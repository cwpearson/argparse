set -x -e

source ci/env.sh

sudo apt-get update 
sudo apt-get install -y --no-install-recommends \
  cmake

