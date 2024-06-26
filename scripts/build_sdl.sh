
#!/bin/bash

pushd $(dirname $0)/..
set -e

INSTALL_DIR=$(pwd)/libs/SDL

rm -f -r extern/SDL/build
rm -f -r $INSTALL_DIR
mkdir -p extern/SDL/build
pushd extern/SDL/build

../configure --prefix=$INSTALL_DIR
make
make install

popd
popd
