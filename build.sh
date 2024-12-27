#!/bin/bash

cmake -S . -B build
cmake --build build

if [ $? -eq 0 ]; then
    echo "Build finished."
else
    echo "Build error." >&2
    exit 1
fi
