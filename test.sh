#!/bin/bash

cd `dirname $0`
shell_dir=`pwd`
build_dir=$shell_dir"/build"

#if [ -d $build_dir ]; then
#  rm -rf $build_dir
#fi
#
#mkdir $build_dir

cd $build_dir
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=debug ..
make -j4
$build_dir/test/kiranwidgets-test/kiran-widget-test
