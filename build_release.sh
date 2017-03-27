#!/bin/sh

mkdir -p build/Release
cd build/Release
cmake -DCMAKE_BUILD_TYPE=Release -DOPENSSL_ROOT_DIR=/opt/build/openssl -DBOOST_ROOT="/opt/build/boost" -DWT_STATIC_ROOT="/opt/build/wt_static" -DSTATIC=ON ../..
make -j8
