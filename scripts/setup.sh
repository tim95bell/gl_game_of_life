
#!/bin/bash

pushd $(dirname $0)/..
set -e

/bin/bash ./scripts/build_glad.sh
/bin/bash ./scripts/build_sdl.sh
