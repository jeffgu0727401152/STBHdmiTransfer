#! /bin/sh

echo "now work in" $(pwd)

for linkfile in $(find . -type l)
do
    libname=${linkfile%.so*}
    echo "process " ${linkfile} "    libname="${libname}
    for binfile in $(find . -type f | grep ${libname})
    do
        echo "    find " ${binfile}
        realbin=${binfile}
    done

    echo "    copy " ${realbin} "to" ${linkfile}
    rm ${linkfile}
    cp ${realbin} ${linkfile}
    echo "done"
    echo "    "
done

echo "all switch done"
