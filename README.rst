******************************************
Graphene Adapter for Intel SGX Driver
******************************************

*Graphene Adapter for Intel SGX Driver for use with the Graphene Library OS*

.. |_| unicode:: 0xa0
   :trim:

This helper repository extracts the required C header from the Intel SGX driver (copied as
``sgx.h``). In particular, this repository contains the script ``link-intel-driver.py`` to find
and copy the required C header from the Intel SGX driver installed on the system. The supported
versions of the Intel SGX driver are:

- DCAP driver, newer versions 1.6+ https://github.com/intel/SGXDataCenterAttestationPrimitives
- DCAP driver, older versions 1.5- https://github.com/intel/SGXDataCenterAttestationPrimitives
- Older out-of-tree non-DCAP driver, only versions 1.9+ https://github.com/intel/linux-sgx-driver
