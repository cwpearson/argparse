set -x -e

source ci/env.sh

which g++
which cmake

g++ --version
cmake --version

mkdir build
cd build
cmake ..
make VERBOSE=1 