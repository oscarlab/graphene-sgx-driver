#!/bin/bash

load_sgx_driver() {
    sudo service aesmd stop
    sudo rmmod graphene_sgx
    sudo rmmod isgx
    make || exit -1
    sudo modprobe isgx || exit -1
    sudo insmod graphene-sgx.ko || exit -1
    sudo service aesmd start || exit -1
}

load_sgx_dcap_driver() {
    sudo rmmod graphene_sgx
    sudo rmmod intel_sgx
    make || exit -1
    sudo modprobe intel_sgx || exit -1
    sudo insmod graphene-sgx.ko || exit -1
}
