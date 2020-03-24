set -x

cd build
env CTEST_OUTPUT_ON_FAILURE=1 make test