#! /bin/bash
rm dict.xdb
#export LD_LIBRARY_PATH=/usr/local/lib
#env | grep '^LD_LIBRARY_PATH'
#build/exe/main/main "$@"
build/install/main/main -c utf8 "$@"
