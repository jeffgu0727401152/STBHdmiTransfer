#! /bin/sh

export APP_PATH=/app
export LIB_PATH=/app/Lib

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$LIB_PATH/BCMLib:$LIB_PATH/nexus:$LIB_PATH/common
export PATH=$PATH:$APP_PATH

chmod 777 $APP_PATH/STBTransfer
chmod 777 $APP_PATH/STBCGI_YW
chmod 777 $APP_PATH/lighttpd/sbin/lighttpd
chmod 777 $APP_PATH/ntpclient

cd $APP_PATH

SERVERIP=$(cat /stb/config/app/serverip.dat)
./ntpclient -s -h $SERVERIP &

killall lighttpd
$APP_PATH/lighttpd/sbin/lighttpd -f $APP_PATH/lighttpd/lighttpd.conf -m $APP_PATH/lighttpd/lib

killall udhcpc

chmod 777 nexus
nexus ./STBTransfer

