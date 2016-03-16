#! /bin/bash
EXE=merge_dict

#export LD_LIBRARY_PATH=/usr/local/lib
#env | grep '^LD_LIBRARY_PATH'
#build/exe/merge_dict/merge_dict "$@"

build/install/$EXE/$EXE -c utf8 "$@"
