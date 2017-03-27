#!/bin/sh

mkdir -p build/Debug
cd build/Debug
cmake -DCMAKE_BUILD_TYPE=Debug -DOPENSSL_ROOT_DIR=/opt/build/openssl -DBOOST_ROOT="/opt/build/boost" -DWT_SHARED_ROOT="/opt/build/wt_shared" -DSTATIC=OFF ../..
make -j8
