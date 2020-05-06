/*
 * (C) Copyright 2020 Intel Corporation
 * Author: Dmitrii Kuvaiskii <dmitrii.kuvaiskii@intel.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2
 * of the License.
 */

#ifndef __ARCH_GSGX_H__
#define __ARCH_GSGX_H__

#ifndef __packed
#define __packed __attribute__((packed))
#endif

#include <linux/stddef.h>
#include <linux/types.h>

#include "sgx.h"

#define GSGX_FILE  "/dev/gsgx"
#define GSGX_MINOR MISC_DYNAMIC_MINOR

/* SGX leaf instruction return values */
#define SGX_SUCCESS             0
#define SGX_INVALID_SIG_STRUCT  1
#define SGX_INVALID_ATTRIBUTE   2
#define SGX_BLKSTATE            3
#define SGX_INVALID_MEASUREMENT 4
#define SGX_NOTBLOCKABLE        5
#define SGX_PG_INVLD            6
#define SGX_LOCKFAIL            7
#define SGX_INVALID_SIGNATURE   8
#define SGX_MAC_COMPARE_FAIL    9
#define SGX_PAGE_NOT_BLOCKED    10
#define SGX_NOT_TRACKED         11
#define SGX_VA_SLOT_OCCUPIED    12
#define SGX_CHILD_PRESENT       13
#define SGX_ENCLAVE_ACT         14
#define SGX_ENTRYEPOCH_LOCKED   15
#define SGX_INVALID_EINITTOKEN  16
#define SGX_PREV_TRK_INCMPL     17
#define SGX_PG_IS_SECS          18
#define SGX_INVALID_CPUSVN      32
#define SGX_INVALID_ISVSVN      64
#define SGX_UNMASKED_EVENT      128
#define SGX_INVALID_KEYNAME     256

/* SGX_INVALID_LICENSE was renamed to SGX_INVALID_EINITTOKEN in SGX driver 2.1:
 *   https://github.com/intel/linux-sgx-driver/commit/a7997dafe184d7d527683d8d46c4066db205758d */
#define SGX_INVALID_LICENSE     SGX_INVALID_EINITTOKEN

#endif /* __ARCH_GSGX_H__ */
