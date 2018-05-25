#! /bin/sh

echo "########## move update program to local present working directory; ##########"
# app.sh在调用此脚本前,已经将远程的Program文件下载并解压到了/stb/config/app/Update/下
echo "/stb/config/app/Update/ folder has" $(ls /stb/config/app/Update/)
mv /stb/config/app/Latest /stb/config/app/Latest_old
mv /stb/config/app/Update/Program /stb/config/app/Latest
sync

if [ `grep -c "DOWNLOADSPEEDLIMIT" /stb/config/app/STBCfg.xml` -ne '0' ]; then
	echo "already have DOWNLOADSPEEDLIMIT in stbcfg, do nothing!"
else
	echo "add DOWNLOADSPEEDLIMIT to stbcfg!"
	sed -i '15a\	DOWNLOADSPEEDLIMIT=\"200000\"' /stb/config/app/STBCfg.xml
fi

rm -rf /stb/config/app/Latest_old
sync

if [ -e /stb/config/app/Latest/ktv.sh ]; then
	echo "########## copy remote program file success !!! ##########"
else
	echo "~~~~~~~~~~ copy remote program file failed !!! ~~~~~~~~~~"
fi

# 酌情决定是否需要更新内存配置,一般不修改底层库无需更改
#echo "########## dd nvram ##########"
#dd if=/stb/config/app/Latest/nvram.bin of=/dev/mmcblk0p2

echo "update done!"

# 酌情决定升级是否需要重启(dd nvram一般需要重启)
#reboot


