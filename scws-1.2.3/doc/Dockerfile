FROM centos:centos7.2.1511
# centos:centos7

RUN yum -y update
RUN yum -y install man sudo which openssh-clients

#RUN yum -y install python-setuptools python-paramiko
#RUN easy_install pip
#RUN pip install ansible

RUN yum -y install epel-release
RUN yum -y install ansible --enablerepo=epel-testing

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

ENV PB yum
COPY pb/${PB}.yml ${PB_HOME}/
RUN sudo chown -R $(id -un):$(id -gn) ${PROVIS_SCRIPTS_HOME}/
RUN ansible-playbook ${PB_HOME}/${PB}.yml -e "hosts=localhost"

ENV PB yum2
COPY pb/${PB}.yml ${PB_HOME}/
RUN sudo chown -R $(id -un):$(id -gn) ${PROVIS_SCRIPTS_HOME}/
RUN ansible-playbook ${PB_HOME}/${PB}.yml -e "hosts=localhost"

COPY env/docker/ ${ENV_HOME}/docker/

#tar curl bzip2 dos2unix
#make gcc gcc-c++
#php

#ENV PRJ_NAME scws
#RUN mkdir -p /usr/local/${PRJ_NAME}
#WORKDIR /usr/local/${PRJ_NAME}
