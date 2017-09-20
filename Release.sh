#!/bin/bash

workspace=$(cd `dirname $0`; pwd)
echo workspace=$workspace

rm -r ${workspace}/Release
mkdir ${workspace}/Release

cp -arf ${workspace}/ReleaseSkeleton/*									${workspace}/Release/

cp -arf ${workspace}/STBCGI_YW/BCM7251SRelease/STBCGI_YW 				${workspace}/Release/Program/
cp -arf ${workspace}/STBTransfer/BCM7251SRelease/STBTransfer 			${workspace}/Release/Program/
cp -arf ${workspace}/Resource/Resource_STBTransfer/Skin_chs.IMG			${workspace}/Release/Program/Images/

cp -arf ${workspace}/HeadLib/Lib/*										${workspace}/Release/Program/Lib/BCMLib/

cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/bcmdriver.ko				${workspace}/Release/Program/Lib/nexus/
cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/libBasicUsageEnvironment.*	${workspace}/Release/Program/Lib/nexus/
cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/libblive_ext.so			${workspace}/Release/Program/Lib/nexus/
cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/libb_os.so					${workspace}/Release/Program/Lib/nexus/
cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/libb_playback_ip.so		${workspace}/Release/Program/Lib/nexus/
cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/libb_psip.so				${workspace}/Release/Program/Lib/nexus/
cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/libgroupsock.*				${workspace}/Release/Program/Lib/nexus/
cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/libliveMedia.*				${workspace}/Release/Program/Lib/nexus/
cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/libnexus.so				${workspace}/Release/Program/Lib/nexus/
cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/libnxpl.so					${workspace}/Release/Program/Lib/nexus/
cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/libtshdrbuilder.so			${workspace}/Release/Program/Lib/nexus/
cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/libUsageEnvironment.*		${workspace}/Release/Program/Lib/nexus/
cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/libv3ddriver.so			${workspace}/Release/Program/Lib/nexus/
cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/wakeup_drv.ko				${workspace}/Release/Program/Lib/nexus/

cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/libal.*					${workspace}/Release/Program/Lib/common/
cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/libcrypto.*				${workspace}/Release/Program/Lib/common/
cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/libcurl.*					${workspace}/Release/Program/Lib/common/
cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/libfcgi.*					${workspace}/Release/Program/Lib/common/
cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/libfreetype.*				${workspace}/Release/Program/Lib/common/
cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/libpng12.*					${workspace}/Release/Program/Lib/common/
cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/libjpeg.*					${workspace}/Release/Program/Lib/common/
cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/libssl.*					${workspace}/Release/Program/Lib/common/
cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/libts*						${workspace}/Release/Program/Lib/common/
cp -arf ${workspace}/ToolChain/BCM7251S/head_lib/lib/libz.*						${workspace}/Release/Program/Lib/common/

#U盘无法接受符号连接,如果希望从u盘启动,则放开下面注释
if [ "$arg" == "udisk" -a -n "$1" ]; then
	echo "release is for usb disk boot!" 
	cd ${workspace}/Release/Program/Lib/nexus/
	sh ${workspace}/link2copy.sh
	cd ${workspace}/Release/Program/Lib/common/
	sh ${workspace}/link2copy.sh
elif [ "$arg" == "factory" -a -n "$1" ]; then
	echo "release is for factory preburn!" 
else
	rm ${workspace}/Release/STBCfg.xml
	rm ${workspace}/Release/app.sh
	echo "release is for normal network mount boot!" 
fi
