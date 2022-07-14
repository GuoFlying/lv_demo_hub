#!/bin/sh
###
 # @Author: Flying
 # @Date: 2021-12-16 09:56:08
 # @LastEditors: Flying
 # @LastEditTime: 2022-06-18 10:39:44
 # @Description: 新建文件
### 

make_op=""
cmake_op=" -DFLYING_PLATFORM=ubuntu"
for param in "$@"
do
    if [ "${param:0:1}" != "-" ]; then
        echo "$param error"
        exit 1
    fi

    if [ "${param:1:1}" == "j" ]; then
        make_op=$param
    fi

    if [ "$param" == "-linuxarm" ]; then
        cmake_op="-D CMAKE_TOOLCHAIN_FILE=./cmake_conf/toolchain.cmake -D FLYING_PLATFORM=linuxarm"
    elif [ "$param" == "-ubntu" ]; then
        cmake_op="-D FLYING_PLATFORM=ubuntu"
    fi
    
    if [ "${param:0:2}" == "-h" ]; then
        echo "eg: $0 -j4"
        echo "eg: $0 -j8 -linuxarm"
        exit 0;
    fi
done

echo "make_op = $make_op "
echo "cmake_op = $cmake_op "

rm build -rf 
mkdir build
cd build
cmake $cmake_op ..
make $make_op