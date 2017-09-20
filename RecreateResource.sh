#!/bin/bash

workspace=$(cd `dirname $0`; pwd)
echo workspace=$workspace
resourcedir=${workspace}/Resource
echo resourcedir=$resourcedir

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${workspace}/STBTool

# Resource_NewUI
rm ${resourcedir}/Resource_STBTransfer/Skin_chs.IMG
rm ${resourcedir}/Resource_STBTransfer/Skin_eng.IMG
${workspace}/STBTool/STBTool -resource ${resourcedir}/Resource_STBTransfer
