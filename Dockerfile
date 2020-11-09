FROM parrotstream/centos-openjdk:8

USER root

ENV CDH_VERSION 6.2.0

ADD cloudera-cdh62.repo /etc/yum.repos.d/
RUN rpm --import https://archive.cloudera.com/cdh6/$CDH_VERSION/redhat7/yum/RPM-GPG-KEY-cloudera
RUN yum install -y gcc-c++ cmake boost-devel impala-udf-devel make
ADD run_tests.sh /run_tests.sh
