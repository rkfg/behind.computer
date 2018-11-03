#!/bin/sh

cd "$(dirname "$0")"
patchelf --set-rpath '$ORIGIN' libs/*
rm -rf build/release
meson --buildtype release -Dwtroot=/opt/build/wt4 build/release
cd build/release
ninja
