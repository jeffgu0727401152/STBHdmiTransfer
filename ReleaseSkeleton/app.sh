#! /bin/sh

########################################################################
#脚本功能:
#
#	该脚本可以放置于/stb/config/app下 或 u盘根目录的/app下,kernel的init进程起来后
#将会会检查这两个位置(优先从u盘下执行该脚本)
#
#	此脚本首先会设置主板自己的IP,设置为/stb/config/app/deviceip.dat文件所指定的IP
#然后会尝试挂载/stb/config/app/serverip.dat中的IP所指定的服务器的/root/STBVerify/Program目录
#(serverip.dat,deviceip.dat等文件由程序认证页点击"认证"写入)
#
#	挂载成功后拷贝服务器/root/STBVerify/Program目录到本地的/app目录,建/networkflag.txt作标志
#将本地/stb/config/app/Log/目录拷贝到服务器的/root/STBVerify/Private/{mac addr}目录
#然后从/app目录执行程序,所有的运行log保存在本地的/stb/config/app/Log/目录(覆盖前次)
#
#	如果serverip.dat不存在 或 该文件指定的服务器无法成功挂载访问, 则改为从本地启动,
#首先link {脚本所在的目录}/Program到/app目录,然后从/app目录执行程序
########################################################################

#directory=$(cd `dirname $0`; pwd)
directory=`pwd`
echo directory=$directory

#network
# 关闭自动获取IP的udhcpc
killall udhcpc

# 从文件获得地址信息
SERVERIP=$(cat /stb/config/app/serverip.dat)
DEVICEIP=$(cat /stb/config/app/deviceip.dat)
MASK=$(cat /stb/config/app/mask.dat)
GATEWAY=$(cat /stb/config/app/gateway.dat)
echo "remote server ip = " ${SERVERIP}
echo "local device ip = " ${DEVICEIP}
echo "local mask = " ${MASK}
echo "local gateway = " ${GATEWAY}

# 配置网络
#udhcpc -b -i eth0
ifconfig eth0 ${DEVICEIP} netmask ${MASK}
route add default gw ${GATEWAY}
ifconfig lo up
hostname STBVod
ifconfig

# 等待5秒,等待网络稳定
sleep 5

# 判断 /app 目录下是否存在数据
FILENUM=$(ls /app -lR | grep "^-" | wc -l)
if [ $FILENUM -gt 0 ]; then
	echo "app folder has data, run directly"
else
	# 挂载远程可执行文件目录
	mkdir /tmpapp
	mount -t nfs -o nolock -o ro $SERVERIP:/root/STBVerify/Program /tmpapp

	if [ $? -eq 0 ]; then
		# 从网络磁盘启动
		echo "run from network..."
		touch /networkflag.txt

		# 网络启动必须copy,防止网络问题导致程序卡死
		mkdir /app
		cp -arf /tmpapp/* /app/
		umount /tmpapp

		mkdir /private
		mount -t nfs -o nolock -o rw $SERVERIP:/root/STBVerify/Private /private

		# get private folder
		MAC=`LANG=C ifconfig eth0 | awk '/HWaddr/{ print $5 }' | sed ''s/://g''`
		PRIVATE_PATH=/private/$MAC
		echo PRIVATE_PATH=$PRIVATE_PATH

		mkdir $PRIVATE_PATH
		chmod 777 $PRIVATE_PATH
		mkdir $PRIVATE_PATH/Log
		chmod 777 $PRIVATE_PATH/Log

		mkdir /stb/config/app/Log

		# 复制上次的 Log
		mv $PRIVATE_PATH/Log/lighttpd.log $PRIVATE_PATH/Log/lighttpd_last.log
		cp /stb/config/app/Log/lighttpd.log $PRIVATE_PATH/Log/lighttpd.log
		mv /stb/config/app/Log/lighttpd.log /stb/config/app/Log/lighttpd_last.log

		mv $PRIVATE_PATH/Log/STBVerify.log $PRIVATE_PATH/Log/STBVerify_Last.log
		cp /stb/config/app/Log/STBVerify.log $PRIVATE_PATH/Log/STBVerify.log
		mv /stb/config/app/Log/STBVerify.log /stb/config/app/Log/STBVerify_last.log

		mv $PRIVATE_PATH/Log/STBCGI.log $PRIVATE_PATH/Log/STBCGI_Last.log
		cp /stb/config/app/Log/STBCGI.log $PRIVATE_PATH/Log/STBCGI.log
		mv /stb/config/app/Log/STBCGI.log /stb/config/app/Log/STBCGI_last.log

		umount /private

	else
		# 从本地执行
		echo "run from local..."
		
		mkdir /stb/config/app/Log
		
		mv /stb/config/app/Log/lighttpd.log /stb/config/app/Log/lighttpd_last.log
		mv /stb/config/app/Log/STBVerify.log /stb/config/app/Log/STBVerify_last.log
		mv /stb/config/app/Log/STBCGI.log /stb/config/app/Log/STBCGI_last.log

		ln -s ${directory}/Program /app
		ln -s ${directory}/Private /private
	fi
fi

chmod 777 /app/ktv.sh
/app/ktv.sh | tee -a /stb/config/app/Log/STBVerify.log

#reboot
