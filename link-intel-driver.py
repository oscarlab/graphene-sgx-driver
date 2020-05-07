#!/usr/bin/env python3

import sys, os, shutil

DRIVER_VERSIONS = {
        'sgx_user.h':                 '/dev/isgx',
        'include/uapi/asm/sgx.h':     '/dev/sgx',
        'include/uapi/asm/sgx_oot.h': '/dev/sgx/enclave',
}

def find_intel_sgx_driver():
    """
    Graphene only needs one header from the Intel SGX Driver:
      - include/uapi/asm/sgx_oot.h for DCAP 1.6+ version of the driver
        (https://github.com/intel/SGXDataCenterAttestationPrimitives)
      - include/uapi/asm/sgx.h for DCAP 1.5- version of the driver
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
        if dev_path == '/dev/sgx' or dev_path == '/dev/sgx/enclave':
            f.write('\n\n#ifndef SGX_DCAP\n#define SGX_DCAP 1\n#endif\n')
        if dev_path == '/dev/sgx/enclave':
            f.write('\n\n#ifndef SGX_DCAP_NEW\n#define SGX_DCAP_NEW 1\n#endif\n')

    this_libraries_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'libraries')
    with open(this_libraries_path, 'w') as f:
        if (os.path.exists('/usr/lib/x86_64-linux-gnu/libsgx_dcap_ql.so') and
                (dev_path == '/dev/sgx' or dev_path == '/dev/sgx/enclave')):
            f.write('-lsgx_dcap_ql')
        else:
            f.write('')  # don't need any additional libraries for old driver

if __name__ == "__main__":
    sys.exit(main())
