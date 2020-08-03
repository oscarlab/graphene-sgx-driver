*******************
Graphene SGX Driver
*******************

*Graphene SGX Driver for use with the Graphene Library OS*

.. |_| unicode:: 0xa0
   :trim:

This helper repository serves two purposes:

- It contains the sources of the Graphene SGX driver (the GSGX driver).
- It extracts the required C header from the Intel SGX driver (copied as
  ``sgx.h``).

The Graphene SGX Driver is a Linux kernel module installed under ``/dev/gsgx``.
Its sole purpose is to enable the ``FSGSBASE`` instruction in user space. Current
Linux versions do not allow enabling this instruction from user land, thus the
need for this driver. In the future, when support for it will be added to Linux,
this driver won't be needed.

**Warning: This module shouldn't be used on production as it introduces a local
privilege escalation vulnerability. Enabling FSGSBASE properly is a much more
complex task and most likely can't be achieved in an out-of-tree driver. If
you're interested in having this feature in production, you should test the
kernel patchset which is currently being upstreamed (the most recent version at
the time of writing:
https://lore.kernel.org/linux-doc/20200528201402.1708239-1-sashal@kernel.org/).
Alternatively, you should use the patchset provided in this repository, which
is the backport for Linux kernel 5.4 LTS (based on the upstream patchset v13
from 28 May 2020).**

Additionally, this repository contains the script ``link-intel-driver.py`` to
find and copy the required C header from the Intel SGX driver installed on the
system. The supported versions of the Intel SGX driver are:

- In-kernel SGX driver, only versions 32+ (https://lkml.org/lkml/2020/7/16/622)
- DCAP driver, newer versions 1.6+ (https://github.com/intel/SGXDataCenterAttestationPrimitives)
- DCAP driver, older versions 1.5- (https://github.com/intel/SGXDataCenterAttestationPrimitives)
- Older out-of-tree non-DCAP driver, only versions 1.9+ (https://github.com/intel/linux-sgx-driver)

To install the Graphene SGX driver, please run:

.. code-block:: sh

   sudo rmmod graphene_sgx || true  # for legacy driver (was previously named `graphene_sgx`)
   sudo rmmod gsgx || true
   make
   sudo insmod gsgx.ko
