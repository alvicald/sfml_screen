#!/bin/bash

BUILD_DIR="$(dirname $(realpath "$0"))/build"
BIN_DIR="$(dirname $(realpath "$0"))/bin"

if [ -d ${BUILD_DIR} ]; then
    rm -rf ${BUILD_DIR}
fi

if [ -d ${BIN_DIR} ]; then
    rm -rf ${BIN_DIR}
fi

cmake -S . -B build && cmake --build build -DCMAKE_BUILD_TYPE=Release

if [ $? -eq 0 ]; then
    echo "Build finished."
else
    echo "Build error." >&2
    exit 1
fi
