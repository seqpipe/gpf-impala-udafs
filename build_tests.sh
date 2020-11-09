#!/bin/bash

cd /code
rm CMakeCache.txt
rm -rf CMakeFiles
cmake .
make
