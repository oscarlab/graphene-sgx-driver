#!/usr/bin/env python3

import sys, os, shutil

DRIVER_VERSIONS = {
        'sgx_user.h':             '/dev/isgx',
        'include/uapi/asm/sgx.h': '/dev/sgx',
}

def find_intel_sgx_driver():
    """
    Graphene only needs one header from the Intel SGX Driver:
      - include/uapi/asm/sgx.h for DCAP version of the driver
        (https://github.com/intel/SGXDataCenterAttestationPrimitives)
      - sgx_user.h for non-DCAP, older version of the driver
        (https://github.com/intel/linux-sgx-driver)

    This function returns the required header from the SGX driver.
    """
    isgx_driver_path = os.getenv("ISGX_DRIVER_PATH")
    if not isgx_driver_path:
        isgx_driver_path = os.path.expanduser(input('Enter the Intel SGX driver dir with C headers: '))

    for header_path, dev_path in DRIVER_VERSIONS.items():
        abs_header_path = os.path.abspath(os.path.join(isgx_driver_path, header_path))
        if os.path.exists(abs_header_path):
            return abs_header_path, dev_path

    raise Exception("Could not find the header from the Intel SGX Driver")


def main():
    """ Find and copy header/device paths from Intel SGX Driver"""
    header_path, dev_path = find_intel_sgx_driver()

    this_header_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'sgx.h')
    shutil.copyfile(header_path, this_header_path)

    with open(this_header_path, 'a') as f:
        f.write('\n\n#ifndef ISGX_FILE\n#define ISGX_FILE "%s"\n#endif\n' % dev_path)


if __name__ == "__main__":
    sys.exit(main())
