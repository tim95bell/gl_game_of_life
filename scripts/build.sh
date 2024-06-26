
#!/bin/bash

pushd $(dirname $0)/..
set -e

BUILD_DIR=./build
rm -r -f $BUILD_DIR
mkdir -p $BUILD_DIR

#-pedantic-errors 
#-Werror
FLAGS="-Wall -g -std=c++17"
SRC_FILES="./src/main.cpp"
#SRC_FILES="./src/main.cpp ./libs/glad/src/glad.c"

clang++ $FLAGS $SRC_FILES -o $BUILD_DIR/main -I./libs/SDL/include -L./libs/SDL/lib -lSDL2 -lm -Wl,-framework,CoreAudio -Wl,-framework,AudioToolbox -Wl,-weak_framework,CoreHaptics -Wl,-weak_framework,GameController -Wl,-framework,ForceFeedback -lobjc -Wl,-framework,CoreVideo -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,IOKit -Wl,-weak_framework,QuartzCore -Wl,-weak_framework,Metal -D_THREAD_SAFE -I./libs/glad/include -L./libs/glad/lib -lglad.o
# -I./extern/sdl/include

popd
