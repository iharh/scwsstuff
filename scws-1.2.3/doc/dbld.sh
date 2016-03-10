#! /bin/bash
set -e
CUR_GROUP=cb-nlp
CUR_NAME=scws
CUR_VER=1.2.3

CUR_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
CTX_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." && pwd )"

$CTX_DIR/dgen.sh $CUR_NAME
docker build -t $CUR_GROUP/$CUR_NAME:$CUR_VER -f $CUR_DIR/Dockerfile $CTX_DIR
