******************************************
Graphene SGX Driver
******************************************

*Graphene SGX Driver for use with the Graphene Library OS*

.. |_| unicode:: 0xa0
   :trim:

This helper repository serves two purposes:

- It contains the sources of the Graphene SGX driver (the GSGX driver).
- It extracts the required C header from the Intel SGX driver (copied as ``sgx.h``).

The Graphene SGX Driver is a Linux kernel module installed under ``/dev/gsgx``. Its sole purpose is
to enable the ``FSGSBASE`` instruction in user space. Older Linux versions do not allow to enable
this instruction from user land, thus the need for this driver. In the future, the support for old
Linux versions may be dropped, and this driver won't be needed.

Additionally, this repository contains the script ``link-intel-driver.py`` to find and copy the
required C header from the Intel SGX driver installed on the system. The supported versions of the
Intel SGX driver are:

- DCAP driver <https://github.com/intel/SGXDataCenterAttestationPrimitives>
- Older out-of-tree non-DCAP driver, only versions 1.9+ <https://github.com/intel/linux-sgx-driver>


To install the Graphene SGX driver, please run::

    sudo rmmod gsgx || true
    sudo rmmod graphene_sgx || true
    make
    sudo insmod gsgx.ko
