#!/bin/bash

workspace=$(cd `dirname $0`; pwd)
echo workspace=$workspace

if [ -d ${workspace}/Release ]; then
	rm -r ${workspace}/Release
fi

mkdir ${workspace}/Release

cp -arf ${workspace}/ReleaseSkeleton/*									${workspace}/Release/

cp -arf ${workspace}/STBCGI_YW/BCM7251SRelease/STBCGI_YW 				${workspace}/Release/Program/
cp -arf ${workspace}/STBTransfer/BCM7251SRelease/STBTransfer 			${workspace}/Release/Program/
cp -arf ${workspace}/Resource/Resource_STBTransfer/Skin_chs.IMG			${workspace}/Release/Program/Images/

cp -arf ${workspace}/ToolChain/BCMLib/Lib/*									${workspace}/Release/Program/Lib/BCMLib/

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

#U盘无法接受符号连接
if [ "$1" == "udisk" ]; then
	echo "release is for usb disk copy!" 
	cd ${workspace}/Release/Program/Lib/nexus/
	sh ${workspace}/link2copy.sh
	cd ${workspace}/Release/Program/Lib/common/
	sh ${workspace}/link2copy.sh
	cd ${workspace}/Release
	echo "tar the Program file..."
	tar -czf Program.tar.gz Program
elif [ "$1" == "factory" ]; then
	rm -r ${workspace}/Release/Private
	cd ${workspace}/Release
	echo "tar the file..." 
	tar -czf Release.tar.gz *
	echo "release is for factory preburn!" 
elif [ "$1" == "deliver" ]; then
	
	rm -r ${workspace}/Release/Private
	cd ${workspace}/Release

	videopath="${workspace}/UdiskSh/open_room_video"
	if [ -d ${videopath} ]; then
		mkdir Video
		if [ "`ls -A ${videopath}`" = "" ]; then
			echo "no default open room video, please place a media file to ${videopath}"
		else
			for file in ${videopath}/*
			do
				if [ -f "$file" ];then
			  		ls -l $file | awk '{print $5}' > $file.size
			  		mv $file.size ./Video/
					cp $file ./Video/
				fi
			done
		fi
	else
		echo "no directory ${workspace}/UdiskSh/open_room_video/ ."
	fi
	echo "tar the file..." 
	tar -czf Release.tar.gz *
	echo "release is for factory preburn!" 
	mkdir ${workspace}/Release/app
	mv Release.tar.gz ./app
	cp ${workspace}/UdiskSh/nvram_copy/* ./app

	mkdir ${workspace}/Release/server
	echo "release is for server update!" 
	rm ${workspace}/Release/STBCfg.xml
	rm ${workspace}/Release/app.sh

	cd ${workspace}/Release
	echo "tar the Program file..."
	tar -czf Program.tar.gz Program

	SW_VER_LINE=$(cat ${workspace}/STBTransfer/Src/Version.h | grep "SW_VERSION")
	SW_VER=${SW_VER_LINE#*\"}
	SW_VER=${SW_VER%\"*}
	echo "version is "${SW_VER}
	echo ${SW_VER} > client_version.txt

	echo "check md5 sum..."
	md5sum Program.tar.gz|cut -d ' ' -f1 >>  client_version.txt

	echo "remove Program/ and Private/"
	rm -rf Program Private
	if [ -d ${videopath} ]; then
		rm -rf Video
	fi
	
	mv Program.tar.gz ./server
	mv client_version.txt ./server

else
	echo "release is for server update!" 
	rm ${workspace}/Release/STBCfg.xml
	rm ${workspace}/Release/app.sh

	cd ${workspace}/Release
	echo "tar the Program file..."
	tar -czf Program.tar.gz Program

	SW_VER_LINE=$(cat ${workspace}/STBTransfer/Src/Version.h | grep "SW_VERSION")
	SW_VER=${SW_VER_LINE#*\"}
	SW_VER=${SW_VER%\"*}
	echo "version is "${SW_VER}
	echo ${SW_VER} > client_version.txt

	echo "check md5 sum..."
	md5sum Program.tar.gz|cut -d ' ' -f1 >>  client_version.txt

	echo "remove Program/ and Private/"
	rm -rf Program Private
fi
