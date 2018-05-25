#! /bin/sh

directory=$(cd `dirname $0`; pwd)
directory_local=`pwd`
COPYFILE_BASE_PATH="/stb/config/app"

echo directory=${directory}
echo directory_local=${directory_local}

app_start_config () {
	APP_SCRIPT="app.sh"
    SCRIPT_APP_PATH="/stb/config/app"
    SCRIPT_APP_NAME="$SCRIPT_APP_PATH/$APP_SCRIPT"
	echo "SCRIPT_APP_PATH=$SCRIPT_APP_PATH"
	echo "SCRIPT_APP_NAME=$SCRIPT_APP_NAME"
	if [ -e  /stb/config/app/app.sh ];then
		touch /factoryflag.txt
		test -e $SCRIPT_APP_NAME && cd $SCRIPT_APP_PATH && . $APP_SCRIPT
		test -e $SCRIPT_APP_NAME && reboot
	fi
}

# mount mmcblk0p7
echo "try to mount mmcblk0p7 to /stb/config."
export tmp=`grep "/dev/mmcblk0p7" /proc/mounts`
echo ${tmp}
if [ -z "${tmp}" ]; then
	echo "the \"/stb/config/\" to be  mounted! "
	if [ -e /stb/config ]; then
		mount -t ext4 /dev/mmcblk0p7 /stb/config
	else
		mkdir -p /stb/config
		mount -t ext4 /dev/mmcblk0p7 /stb/config
	fi
else
	echo "the \"/stb/config/\" has mounted! "
fi

# do the factory copy
echo "copy the Release.tar.gz from usb disk"
if [ -a "$COPYFILE_BASE_PATH" ]; then
	rm -rf ${COPYFILE_BASE_PATH}
fi

mkdir ${COPYFILE_BASE_PATH}
cd ${COPYFILE_BASE_PATH}
cp ${directory_local}/Release.tar.gz Release.tar.gz
tar -zxf Release.tar.gz
rm Release.tar.gz
sync

echo "########## dd nvram from usb disk file ##########"
dd if=${directory_local}/nvram.bin of=/dev/mmcblk0p2

if [ -e /stb/config/app/STBCfg.xml ]; then
	echo "########## copy usb disk file success !!! ##########"
else
	echo "~~~~~~~~~~ copy usb disk file failed !!! ~~~~~~~~~~"
	echo "~~~~~~~~~~ so, reboot to try again !!! ~~~~~~~~~~"
	sleep 4
	reboot
fi

# do the factory test
app_start_config
