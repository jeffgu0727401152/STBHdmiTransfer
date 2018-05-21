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
echo "directory=${directory}"

#network
# 关闭自动获取IP的udhcpc
killall udhcpc

# 从文件获得地址信息
SERVERIP=$(cat ${directory}/serverip.dat)
DEVICEIP=$(cat ${directory}/deviceip.dat)
MASK=$(cat ${directory}/mask.dat)
GATEWAY=$(cat ${directory}/gateway.dat)
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

# 不存在则建立本地日志目录
if [ ! -d "${directory}/Log" ]; then
	mkdir ${directory}/Log
fi
# 不存在则建立保存最新程序的目录
if [ ! -d "${directory}/Latest" ]; then
	mkdir ${directory}/Latest
fi

# 判断 /app 目录下是否存在数据
FILENUM=$(ls /app -lR | grep "^-" | wc -l)
if [ $FILENUM -gt 0 ]; then
	echo "app folder has data, run directly"
else
	# 挂载远程可执行文件目录
	echo "try mount remote server Program to /program folder..."
	mkdir /program
	mount -t nfs -o nolock -o ro $SERVERIP:/root/STBVerify/Program /program
	if [ $? -eq 0 ]; then
		# 从网络获取过最新的信息启动
		echo "run from network..."
		touch /networkflag.txt

		#获取网络program的版本与本地的版本,使用echo是为了去除字串中多余的空格,为后续的字符串比较做准备
		if [ -f "/program/version.dat" ]; then
			SERVER_VER=$(echo $(cat /program/version.dat))
		else
			SERVER_VER="unknown"
		fi
		echo "server program version is ${SERVER_VER}"

		if [ -f "${directory}/Latest/version.dat" ]; then
			LOCAL_VER=$(echo $(cat /stb/config/app/Latest/version.dat))
		else
			LOCAL_VER="unknown"
		fi
		echo "local program version is ${LOCAL_VER}"

		# 如果服务器上没有version.dat则无法更新
		if [ "$SERVER_VER" != "unknown" ] && [ "$SERVER_VER" != "$LOCAL_VER" ];then
			echo "SERVER_VER != LOCAL_VER, copy update.sh and exec it"
			cp /program/update.sh /update.sh
			chmod 777 /update.sh
			/update.sh
		fi

		umount /program
		echo "check remote server Program done!"
	else
		# 没有挂载成功远程目录,所以算是从本地执行
		echo "run from local..."
	fi
fi

# 准备日志文件
# 程序执行过程中的log都保存在不带last结尾的日志文件中
# 所以在程序实际执行之前,将上次的log重命名为last结尾的文件
echo "try mount remote server Private to /private folder..."
mkdir /private
mount -t nfs -o nolock -o rw $SERVERIP:/root/STBVerify/Private /private
if [ $? -eq 0 ] && [ -f "/private/uploadlog.dat" ]; then
	echo "server need log, upload log to server"
	# 获取本设备在服务器上保存日志的目录
	MAC=`LANG=C ifconfig eth0 | awk '/HWaddr/{ print $5 }' | sed ''s/://g''`
	REMOTE_PRIVATE_PATH=/private/$MAC
	echo "REMOTE_PRIVATE_PATH=${REMOTE_PRIVATE_PATH}"

	mkdir $REMOTE_PRIVATE_PATH
	chmod 777 $REMOTE_PRIVATE_PATH
	mkdir $REMOTE_PRIVATE_PATH/Log
	chmod 777 $REMOTE_PRIVATE_PATH/Log

	# 复制上次的 Log
	mv $REMOTE_PRIVATE_PATH/Log/lighttpd.log $REMOTE_PRIVATE_PATH/Log/lighttpd_last.log
	cp ${directory}/Log/lighttpd.log $REMOTE_PRIVATE_PATH/Log/lighttpd.log
	mv ${directory}/Log/lighttpd.log ${directory}/Log/lighttpd_last.log

	mv $REMOTE_PRIVATE_PATH/Log/STBVerify.log $REMOTE_PRIVATE_PATH/Log/STBVerify_Last.log
	cp ${directory}/Log/STBVerify.log $REMOTE_PRIVATE_PATH/Log/STBVerify.log
	mv ${directory}/Log/STBVerify.log ${directory}/Log/STBVerify_last.log

	mv $REMOTE_PRIVATE_PATH/Log/STBCGI.log $REMOTE_PRIVATE_PATH/Log/STBCGI_Last.log
	cp ${directory}/Log/STBCGI.log $REMOTE_PRIVATE_PATH/Log/STBCGI.log
	mv ${directory}/Log/STBCGI.log ${directory}/Log/STBCGI_last.log
	echo "copy local log to remote server Private folder done!"
	umount /private
else
	mv ${directory}/Log/lighttpd.log /${directory}/Log/lighttpd_last.log
	mv ${directory}/Log/STBVerify.log ${directory}/Log/STBVerify_last.log
	mv ${directory}/Log/STBCGI.log ${directory}/Log/STBCGI_last.log
fi

# 判断版权盒上除了出厂预装的版本外,是否存在从服务器下载的新版
if [ -f "${directory}/Latest/ktv.sh" ]; then
	ln -s ${directory}/Latest /app
else
	ln -s ${directory}/Program /app
fi

echo "/app folder has" $(ls /app)

# 实际开始执行程序
echo "prepare program and log done! exec /app/ktv.sh..."
chmod 777 /app/ktv.sh
/app/ktv.sh | tee -a ${directory}/Log/STBVerify.log

#reboot
