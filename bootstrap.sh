#!/bin/bash 
BUILD_DIR=build

if [ -d "$BUILD_DIR" ]; then
    rm -rf $BUILD_DIR
fi

mkdir $BUILD_DIR
pushd $BUILD_DIR
cmake -GNinja -DCMAKE_EXPORT_COMPILE_COMMANDS=1 .. 
ninja
cp compile_commands.json .. 
popd