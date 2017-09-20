#! /bin/sh

echo work in $(pwd)

for linkfile in $(find . -type l)
do 
    for binfile in $(find . -type f | grep ${linkfile})
    do
        realbin=${binfile}
    done

    echo "find link:" $linkfile "(switch it with:" ${realbin} ")"
    rm ${linkfile}
    cp ${realbin} ${linkfile}
done

echo "switch done"
