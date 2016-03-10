#! /bin/bash
set -e
GUEST_USER_NAME=scws
FILES_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/files" && pwd )"

ADD_USER_FILE=$FILES_DIR/add_host_user.sh
if ! [[ -f $ADD_USER_FILE ]]; then
  GUEST_GROUP_NAME=$GUEST_USER_NAME

  echo $ADD_USER_FILE does not exists - generating
  echo '#! /bin/sh' > $ADD_USER_FILE
  echo groupadd $GUEST_GROUP_NAME -f -g $(id -g) >> $ADD_USER_FILE
  echo useradd $GUEST_USER_NAME -l -u $(id -u) -g $(id -g) -G wheel >> $ADD_USER_FILE
fi
