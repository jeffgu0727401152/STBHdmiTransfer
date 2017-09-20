#! /bin/sh

directory=$(cd `dirname $0`; pwd)
#directory=`pwd`
echo directory=$directory

#network
killall udhcpc
udhcpc -b -i eth0
ifconfig lo up

hostname STBVod

# 判断 /app 目录下是否存在数据
FILENUM=$(ls /app -lR | grep "^-" | wc -l)
if [ $FILENUM -gt 0 ]; then
	echo "app folder has data, run directly"
else
	# 获取serverIP
	SERVERIP=$(cat /stb/config/app/serverip.dat)
	mkdir /tmpapp
	mount -t nfs -o nolock -o ro $SERVERIP:/root/STBVerify/Program /tmpapp

	if [ $? -eq 0 ]; then
		# 从网络磁盘启动
		echo "run from network..."
		touch /networkflag.txt

		#网络启动必须copy,防止网络问题导致程序卡死
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

		mv $PRIVATE_PATH/Log/STBVerify.log $PRIVATE_PATH/Log/STBVerify_Last.log
		cp /stb/config/app/Log/STBVerify.log $PRIVATE_PATH/Log/STBVerify.log

		mv $PRIVATE_PATH/Log/STBCGI.log $PRIVATE_PATH/Log/STBCGI_Last.log
		cp /stb/config/app/Log/STBCGI.log $PRIVATE_PATH/Log/STBCGI.log

        umount /private

	else
		# 从本地执行
		echo "run from local..."
		
		mkdir /stb/config/app/Log
		
		mv /stb/config/app/Log/lighttpd.log /stb/config/app/lighttpd_last.log
		mv /stb/config/app/Log/STBVerify.log /stb/config/app/STBVerify_last.log
		mv /stb/config/app/Log/STBCGI.log /stb/config/app/STBCGI_last.log

		ln -s /stb/config/app/Program /app
		ln -s /stb/config/app/Private /private
	fi
fi

chmod 777 /app/ktv.sh
/app/ktv.sh | tee -a /stb/config/app/Log/STBVerify.log

#reboot
