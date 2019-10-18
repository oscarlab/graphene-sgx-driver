#!/usr/bin/env python3

import sys, os, re, readline, subprocess

isgx_repo    = 'https://github.com/intel/linux-sgx-driver.git'
isgx_path    = os.getenv("ISGX_DRIVER_PATH")
isgx_version = os.getenv("ISGX_DRIVER_VERSION")

try:
    # get the locations of directories
    print('''
*****************************************************************"
Make sure you have downloaded and installed the Intel SGX driver"
from {0}."
*****************************************************************

'''.format(isgx_repo))

    while True:
        if not isgx_path:
            isgx_path = os.path.expanduser(input(
                'Enter the Intel SGX driver directory (can be absolute/relative path, or start with ~ or ~USERNAME): '))

            # clone the repo if not exist
            if not os.path.exists(isgx_path):
                iput = input(
                    'directory {0} does not exist; clone the driver here? ([n]/y): '.format(isgx_path)).lower()
                if iput == 'y':
                    subprocess.check_call('git clone {0} {1}'.format(isgx_repo, isgx_path), shell=True)

        if os.path.exists(isgx_path + '/sgx.h'):
            break
        if os.path.exists(isgx_path + '/isgx.h'):
            break
        print('{0} is not a directory for the Intel SGX driver'.format(isgx_path))
        isgx_path = None

    # get the driver version
    while True:
        if not isgx_version:
            isgx_version = input('Enter the driver version (default: 2.1+): ')
        if not isgx_version:
            isgx_version_major = 2
            isgx_version_minor = 1
            break
        m = re.match('([1-9])\.([0-9]+)', isgx_version)
        if m:
            isgx_version_major = m.group(1)
            isgx_version_minor = m.group(2)
            break
        print('{0} is not a valid version (x.xx)'.format(isgx_version))
        isgx_version = None

    # create a symbolic link called 'linux-sgx-driver'
    isgx_link = 'linux-sgx-driver'
    print(isgx_link + ' -> ' + isgx_path)
    if os.path.exists(isgx_link):
        os.unlink(isgx_link)
    os.symlink(isgx_path, isgx_link)

    # create isgx_version.h
    with open('isgx_version.h', 'w') as versionfile:
        print('create isgx_version.h')
        print('''#include <linux/version.h>

#define SDK_DRIVER_VERSION KERNEL_VERSION({0}, {1}, 0)
#define SDK_DRIVER_VERSION_STRING "{0}.{1}"'''.format(isgx_version_major, isgx_version_minor), file=versionfile)

except:
    print('uh-oh: {0}'.format(sys.exc_info()[0]))
    exit(-1)
