#! /bin/sh

########################################################################
#脚本功能:
#
#	该脚本可以放置于/stb/config/app下 或 u盘根目录的/app下,kernel的init进程起来后
#将会会检查这两个位置(优先从u盘下执行该脚本)
#
#	此脚本首先会设置主板自己的IP,设置为/stb/config/app/deviceip.dat文件所指定的IP
#	
#	如果上次运行留有上次程序的log，那么log将会加上_last描述名进行保存
#   
#	检查上次程序运行是否保留了需要升级的安装包和相关的tag文件，并根据此情况将升级包内的update.sh拷贝至根目录并执行
#   
#	如果版权盒上除了出厂预装的版本外,未存在从服务器下载的版，那么直接运行/stb/config/app/Program下的出厂程序
#
########################################################################

#directory=$(cd `dirname $0`; pwd)
directory=`pwd`
echo "directory=${directory}"

#network
# 关闭自动获取IP的udhcpc
killall udhcpc

# 从文件获得地址信息
SERVERIP=$(cat ${directory}/serverip.dat)
DEVICEIP=$(cat ${directory}/deviceip.dat)
MASK=$(cat ${directory}/mask.dat)
GATEWAY=$(cat ${directory}/gateway.dat)
echo "remote server ip = " ${SERVERIP}
echo "local device ip = " ${DEVICEIP}
echo "local mask = " ${MASK}
echo "local gateway = " ${GATEWAY}

# 配置网络
#udhcpc -b -i eth0
ifconfig eth0 ${DEVICEIP} netmask ${MASK}
route add default gw ${GATEWAY}
ifconfig lo up
hostname STBVod

# 打印出网络配置信息
ifconfig

# 不存在则建立本地日志目录
if [ ! -d "${directory}/Log" ]; then
	mkdir ${directory}/Log
fi

# 不存在则创建新的lastLogIndex.flag
if [ ! -f "${directory}/Log/lastLogIndex.flag" ]; then
	touch ${directory}/Log/lastLogIndex.flag
	echo 0 > ${directory}/Log/lastLogIndex.flag
fi

# 不存在则建立保存最新程序的目录
if [ ! -d "${directory}/Latest" ]; then
	mkdir ${directory}/Latest
fi
# 不存在则建立更新最新程序的目录
if [ ! -d "${directory}/Update" ]; then
	mkdir ${directory}/Update
fi

# 判断 /app 目录下是否存在数据
FILENUM=$(ls /app -lR | grep "^-" | wc -l)
if [ $FILENUM -gt 0 ]; then
	echo "app folder has data, run directly"
else
	# 识别本次启动是否需要更新程序
	if [ -f "${directory}/Update/update.flag" ]; then
		echo "found update.flag, copy update.sh to root directory"
		cd ${directory}/Update/
		tar -zxf Program.tar.gz
		cp Program/update.sh /update.sh
		
		# 开始执行 update.sh
		echo "exec update.sh..."
		chmod 777 /update.sh
		/update.sh
		cp -f ${directory}/Update/client_version.txt ${directory}/Latest/
		echo "########## remove /stb/config/app/Update/* ... ##########"
		rm -rf ${directory}/Update/*
		
	else
		# 没有识别到本次启动需要更新,所以从本地执行
		echo "mormal run..."
	fi
fi

# 准备日志文件
# 程序执行过程中的log保存在不带last结尾的日志文件中
# 根据需求，需要保留最近5份的开机log供查验，
# 本次为XXX.log,历史log文件为XXX_last[num].log
# 假设lastLogIndex.flag 文件内数字为n,从最近的上一次历史开机开始，到最近5次之前的log顺序为 n,n-1,...,0,4,4-1,...,n+1
# 未满5次时依常规次序由前向后到不存在序号对应文件为止

# u盘烧录头次运行时上次的log是不存在的
if [ -f "${directory}/Log/STBVerify.log" ]; then
	LOG_INDEX_LAST=$(cat ${directory}/Log/lastLogIndex.flag)
	LOG_INDEX_CURRENT_TMP=$((${LOG_INDEX_LAST}+1))
	LOG_INDEX_CURRENT=$((${LOG_INDEX_CURRENT_TMP}%5))
	echo ${LOG_INDEX_CURRENT} > ${directory}/Log/lastLogIndex.flag
	sync
	echo "current log index is" $LOG_INDEX_CURRENT

	mv ${directory}/Log/lighttpd.log ${directory}/Log/lighttpd_last$LOG_INDEX_CURRENT.log
	mv ${directory}/Log/STBVerify.log ${directory}/Log/STBVerify_last$LOG_INDEX_CURRENT.log
	mv ${directory}/Log/STBCGI.log ${directory}/Log/STBCGI_last$LOG_INDEX_CURRENT.log
fi

# 判断版权盒上除了出厂预装的版本外,是否存在从服务器下载的新版
if [ -f "${directory}/Latest/ktv.sh" ]; then
	echo "found latest version,exec the latest version now..."
	# 现在这个flag用于指示程序是否是从最新的目录启动的,用于区别出厂的
	touch /networkflag.txt
	ln -s ${directory}/Latest /app
else
	echo "no latest version,exec the factory version now..."
	ln -s ${directory}/Program /app
fi

echo "/app folder has" $(ls /app)

# 实际开始执行程序
echo "prepare program and log done! exec /app/ktv.sh..."
chmod 777 /app/ktv.sh
/app/ktv.sh | tee -a ${directory}/Log/STBVerify.log

#reboot
