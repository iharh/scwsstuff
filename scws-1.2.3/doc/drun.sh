#! /bin/bash
#./drun.sh "../prepare.sh && gradle clean runAcceptanceTests"
set -e
#set -x;
CTX_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." && pwd )"
. $CTX_DIR/env-vars.sh

RUN_CMD="$@"
if [[ -z "$RUN_CMD" ]]; then
  RUN_FLAGS="--rm -ti"
  RUN_PREF=
  RUN_CMD=/bin/bash
else
  #RUN_FLAGS=
  RUN_PREF="/bin/bash -cl"
fi
#echo RUN: $RUN_PREF "$RUN_CMD"
#echo RUN_FLAGS: $RUN_FLAGS
#echo RUN_PORT_MAP: $RUN_PORT_MAP
#echo RUN_PREF: $RUN_PREF
#echo RUN_CMD: $RUN_CMD

docker run $RUN_FLAGS\
 $RUN_PORT_MAP\
 $CUR_GROUP/$CUR_NAME:$CUR_VER\
 $RUN_PREF "$RUN_CMD"
