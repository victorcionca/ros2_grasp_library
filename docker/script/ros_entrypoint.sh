#!/bin/bash

set -e

# setup ros2 environment
source /opt/ros/dashing/setup.bash

source /root/ros2_ws/install/setup.bash

exec "$@"
