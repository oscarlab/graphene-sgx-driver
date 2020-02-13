#!/bin/bash

sudo service aesmd stop
sudo rmmod graphene_sgx  # for lingering old version of gsgx
sudo rmmod gsgx
sudo rmmod isgx
make || exit -1
sudo modprobe isgx || exit -1
sudo insmod gsgx.ko || exit -1
sudo service aesmd start || exit -1
