#! /bin/bash
#./drun.sh "../prepare.sh && gradle clean runAcceptanceTests"
set -e
#set -x;
CUR_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
. $CUR_DIR/scws-1.2.3/env-vars.sh

RUN_ARGS="$@"

docker run --rm -ti\
 -v $CUR_DIR:/project\
 -w /project\
 $CUR_GROUP/$CUR_NAME:$CUR_VER\
 scws -c utf8 -r /home/scws/scws/etc/rules.utf8.ini -d /home/scws/scws/dev/dict/dict.utf8.txt -A "$RUN_ARGS"
 
# /bin/bash -cl "pwd"
# /bin/bash -cl "ls -la"
