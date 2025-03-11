#!/bin/sh

build_dir=$(pwd)/build
rm -rf ${build_dir}
mkdir ${build_dir}
cd ${build_dir}
cmake ..
make
# cp ${build_dir}/gridmap ${build_dir}/../gridmap
cp ${build_dir}/gridmap_lib ${build_dir}/../gridmap_lib
rm -rf ${build_dir}

# # 安装动态库脚本
# build_dir=$(pwd)/build
# rm -rf ${build_dir}
# mkdir ${build_dir}
# cd ${build_dir}
# cmake ..
# make
# make install
# rm -rf ${build_dir}