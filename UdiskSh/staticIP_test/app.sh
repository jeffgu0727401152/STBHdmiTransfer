#! /bin/sh

#directory=$(cd `dirname $0`; pwd)
directory=`pwd`
echo directory=$directory

# 判断 /app 目录下是否存在数据
FILENUM=$(ls /app -lR | grep "^-" | wc -l)
if [ $FILENUM -gt 0 ]; then
	echo "app folder has data, run directly"
else
	# 从本地执行
	echo "run from local..."

	touch /factoryflag.txt

	mkdir /stb/config/app/Log

	mv /stb/config/app/Log/lighttpd.log /stb/config/app/Log/lighttpd_last.log
	mv /stb/config/app/Log/STBVerify.log /stb/config/app/Log/STBVerify_last.log
	mv /stb/config/app/Log/STBCGI.log /stb/config/app/Log/STBCGI_last.log

	ln -s /stb/config/app/Program /app
	ln -s /stb/config/app/Private /private
fi

chmod 777 /app/ktv.sh
/app/ktv.sh | tee -a /stb/config/app/Log/STBVerify.log

#reboot
