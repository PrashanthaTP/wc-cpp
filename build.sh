#!/bin/env bash
[ -f env.sh ] && source env.sh && echo "Sourced env.sh"
echo -en "\e[33;1m"
echo -e "CC : ${CC}"
echo -e "CXX: ${CXX}"
echo -en "\e[0m"

cmake -S . -B build -G 'MinGW Makefiles' && { cmake --build build ; }
