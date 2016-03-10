FROM centos:centos7

RUN yum -y update && yum -y install man tar curl bzip2 dos2unix make gcc gcc-c++

ENV PRJ_NAME scws
RUN mkdir -p /usr/local/${PRJ_NAME}
WORKDIR /usr/local/${PRJ_NAME}
