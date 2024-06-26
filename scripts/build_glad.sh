
#!/bin/bash

pushd $(dirname $0)/..
set -e

LIBS_DIR=$(pwd)/libs
INSTALL_DIR=$LIBS_DIR/glad

rm -f -r $INSTALL_DIR/lib
mkdir -p $INSTALL_DIR/lib

clang -c $INSTALL_DIR/src/glad.c -I$INSTALL_DIR/include -o $INSTALL_DIR/lib/glad.o

popd
