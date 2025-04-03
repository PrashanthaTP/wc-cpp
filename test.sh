#!/bin/env bash
#
cmake --build build/test && cd build/test && ctest ${@}
