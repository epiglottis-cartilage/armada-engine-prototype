#!/bin/bash

if [ $# -lt 1 ]; then
    echo "too few or too much params"
    echo "usage: $0 ./programpath"
    exit 1
fi

__NV_PRIME_RENDER_OFFLOAD=1 \
__GLX_VENDOR_LIBRARY_NAME=nvidia \
__VK_LAYER_NV_optimus=NVIDIA_only \
__GLX_DEVICE_ID=0 \
__GLVND_DISALLOW_PATCHING=1 \
"$1"