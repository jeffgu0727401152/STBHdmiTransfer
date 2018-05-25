#! /bin/sh

#directory=$(cd `dirname $0`; pwd)
directory=`pwd`
echo directory=$directory

# waiting for ip address
echo -e "Waiting for eth0 ready\c"

while [ "$eth0_addr" == "" ]; do
eth0_addr=`ifconfig eth0 | grep "inet addr"`
eth0_addr=${eth0_addr#*:}
eth0_addr=${eth0_addr%% *}
echo -e ".\c"
sleep 1
done

echo ""
echo "eth0 is ready! ip address:$eth0_addr"

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
