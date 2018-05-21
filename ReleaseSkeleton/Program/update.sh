#! /bin/sh
echo "########## copy remote program to local ##########"
# app.sh在调用此脚本前,已经将远程的Program目录,挂载在/program下了
cp -arf /program/* /stb/config/app/Latest/

echo "/program folder has" $(ls /program)

if [ -e /stb/config/app/Latest/ktv.sh ]; then
	echo "########## copy remote program file success !!! ##########"
else
	echo "~~~~~~~~~~ copy remote program file failed !!! ~~~~~~~~~~"
fi

# 酌情决定是否需要更新内存配置,一般不修改底层库无需更改
#echo "########## dd nvram ##########"
#dd if=/stb/config/app/Latest/nvram.bin of=/dev/mmcblk0p2

sync
echo "update done!"

# 酌情决定升级是否需要重启(dd nvram一般需要重启)
#reboot


