export XHAL_ROOT=$(dirname "${BASH_SOURCE[0]}")
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$XHAL_ROOT/lib
export PATH=$PATH:$XHAL_ROOT/python/reg_interface
