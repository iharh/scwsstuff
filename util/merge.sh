#! /bin/bash
EXE=merge

#export LD_LIBRARY_PATH=/usr/local/lib
#env | grep '^LD_LIBRARY_PATH'
#build/exe/$EXE/$EXE "$@"

build/install/$EXE/$EXE "$@"
