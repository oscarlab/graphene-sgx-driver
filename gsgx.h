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

/* SGX_INVALID_LICENSE was renamed to SGX_INVALID_EINITTOKEN in SGX driver 2.1:
 *   https://github.com/intel/linux-sgx-driver/commit/a7997dafe184d7d527683d8d46c4066db205758d */
#if !defined(SGX_INVALID_LICENSE) && !defined(SGX_INVALID_EINITTOKEN)
#error "Cannot find SGX_INVALID_LICENSE nor SGX_INVALID_EINITTOKEN in Linux SGX Driver headers"
#endif

#if !defined(SGX_INVALID_LICENSE)
#define SGX_INVALID_LICENSE SGX_INVALID_EINITTOKEN
#endif

#endif /* __ARCH_GSGX_H__ */
