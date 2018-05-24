#! /bin/sh

echo "########## move update program to local present working directory; ##########"
# app.sh在调用此脚本前,已经将远程的Program文件下载并解压到了/stb/config/app/Update/下
mv /stb/config/app/Update/Program/* /stb/config/app/Latest/

echo "/stb/config/app/Update/ folder has" $(ls /stb/config/app/Update/)

if [ -e /stb/config/app/Latest/ktv.sh ]; then
	echo "########## copy remote program file success !!! ##########"
else
	echo "~~~~~~~~~~ copy remote program file failed !!! ~~~~~~~~~~"
fi

sync

# 酌情决定是否需要更新内存配置,一般不修改底层库无需更改
#echo "########## dd nvram ##########"
#dd if=/stb/config/app/Latest/nvram.bin of=/dev/mmcblk0p2

echo "update done!"

# 酌情决定升级是否需要重启(dd nvram一般需要重启)
#reboot


