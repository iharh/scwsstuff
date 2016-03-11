FROM centos:centos7.2.1511
# centos:centos7.2.1511
# centos:centos7

RUN yum -y update && yum clean all
RUN yum -y install httpd && yum clean all
RUN yum -y install man sudo which openssh-clients

RUN yum -y install python-setuptools python-paramiko
RUN easy_install pip
RUN pip install ansible

# Edit sudoers file
# To avoid error: sudo: sorry, you must have a tty to run sudo
RUN sed -i -e "s/Defaults    requiretty.*/Defaults    !requiretty/g" /etc/sudoers

# Fully quoted because of the ': ' on the line
RUN ansible localhost -m lineinfile -a "dest=/etc/sudoers state=present regexp='^%wheel' line='%wheel ALL=(ALL) NOPASSWD: ALL'"

#
# create user
#
ENV USER_NAME root
ENV USER_HOME /${USER_NAME}

ENV FILES_HOME files

ENV SCRIPT add_host_user
COPY ${FILES_HOME}/${SCRIPT}.sh ${USER_HOME}/
RUN sudo chown -R ${USER_NAME}:${USER_NAME} ${USER_HOME}/${SCRIPT}.sh
RUN sudo chmod +x ${USER_HOME}/${SCRIPT}.sh
RUN ${USER_HOME}/${SCRIPT}.sh

ENV USER_NAME scws
ENV CUR_VER 1.2.3
ENV USER_HOME /home/${USER_NAME}
#ENV USER_GRP wheel

WORKDIR ${USER_HOME}
USER ${USER_NAME}

#
# incremental steps - for docker only
#

ENV PROVIS_SCRIPTS_HOME ${USER_HOME}/provis
ENV PB_HOME ${PROVIS_SCRIPTS_HOME}/pb
ENV ENV_HOME ${PROVIS_SCRIPTS_HOME}/env
ENV ROLES_HOME ${PROVIS_SCRIPTS_HOME}/roles
ENV FILES_HOME files

COPY env/docker/ ${ENV_HOME}/docker/

ENV PB pack-base
COPY pb/${PB}.yml ${PB_HOME}/
RUN sudo chown -R $(id -un):$(id -gn) ${PROVIS_SCRIPTS_HOME}/
RUN ansible-playbook ${PB_HOME}/${PB}.yml -e "hosts=localhost"

ENV PB pack-dev
COPY pb/${PB}.yml ${PB_HOME}/
RUN sudo chown -R $(id -un):$(id -gn) ${PROVIS_SCRIPTS_HOME}/
RUN ansible-playbook ${PB_HOME}/${PB}.yml -e "hosts=localhost"

ENV PB pack-php
COPY pb/${PB}.yml ${PB_HOME}/
RUN sudo chown -R $(id -un):$(id -gn) ${PROVIS_SCRIPTS_HOME}/
RUN ansible-playbook ${PB_HOME}/${PB}.yml -e "hosts=localhost"

COPY ${FILES_HOME}/wandisco-git.repo /etc/yum.repos.d/wandisco-git.repo
#RUN sudo chown -R $(id -un):$(id -gn) ${FILES_HOME}/

ENV PB pack-vcs
COPY pb/${PB}.yml ${PB_HOME}/
RUN sudo chown -R $(id -un):$(id -gn) ${PROVIS_SCRIPTS_HOME}/
RUN ansible-playbook ${PB_HOME}/${PB}.yml -e "hosts=localhost"


#ENV PB php
#COPY pb/${PB}.yml ${PB_HOME}/
#COPY roles/ansible-role-php/ ${ROLES_HOME}/ansible-role-php/
#RUN sudo chown -R $(id -un):$(id -gn) ${PROVIS_SCRIPTS_HOME}/
#RUN ANSIBLE_ROLES_PATH=${ROLES_HOME} ansible-playbook ${PB_HOME}/${PB}.yml -e @${ENV_HOME}/docker/extra-vars.json -e "hosts=localhost"

##ENV PRJ_NAME scws
##RUN mkdir -p /usr/local/${PRJ_NAME}
##WORKDIR /usr/local/${PRJ_NAME}

ENV ARC_NAME ${USER_NAME}-${CUR_VER}
COPY ${FILES_HOME}/${ARC_NAME}.tar.bz2 ${USER_HOME}/
RUN tar -xvjf ${ARC_NAME}.tar.bz2

WORKDIR ${USER_HOME}/${ARC_NAME}
RUN ./configure
RUN make
RUN sudo make install

WORKDIR ${USER_HOME}
RUN git clone https://github.com/hightman/${USER_NAME}.git

#
# gen chs dict
#
WORKDIR ${USER_HOME}/${USER_NAME}/dev/dict
RUN php calc_text.php > dict.txt
RUN php -r 'echo mb_convert_encoding(file_get_contents("dict.txt"), "utf-8", "gbk");' > dict.utf8.txt
RUN scws-gen-dict -c utf8 -i dict.utf8.txt -o dict.utf8.xdb

#
# copy cht dict
COPY ${FILES_HOME}/dict_cht.utf8.xdb ${USER_HOME}/${USER_NAME}/dev/dict

WORKDIR ${USER_HOME}

ENV SCRIPT scli
COPY ${FILES_HOME}/${SCRIPT}.sh ${USER_HOME}/
RUN sudo chmod +x ${USER_HOME}/${SCRIPT}.sh
RUN sudo chown -R ${USER_NAME}:${USER_NAME} ${USER_HOME}/${SCRIPT}.sh

ENV SCRIPT tcli
COPY ${FILES_HOME}/${SCRIPT}.sh ${USER_HOME}/
RUN sudo chmod +x ${USER_HOME}/${SCRIPT}.sh
RUN sudo chown -R ${USER_NAME}:${USER_NAME} ${USER_HOME}/${SCRIPT}.sh

#
# sample data
#
COPY ${FILES_HOME}/s1.txt ${USER_HOME}/

#
# volumes
#

VOLUME  [\
  "/project"\
]
