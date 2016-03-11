#! /bin/bash
CUR_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
. $CUR_DIR/scws-1.2.3/env-vars.sh
docker run --rm -ti\
 -v $(pwd):/project\
 -w /project\
 $CUR_GROUP/$CUR_NAME:$CUR_VER\
 scws -c utf8 -r /home/scws/scws/etc/rules_cht.utf8.ini -d /home/scws/scws/dev/dict/dict_cht.utf8.xdb -A "$@"
