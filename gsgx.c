/*
 * (C) Copyright 2020 Intel Corporation
 * Author: Dmitrii Kuvaiskii <dmitrii.kuvaiskii@intel.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2
 * of the License.
 */

/*
 * The only action this driver does is enabling FSGSBASE instruction in user
 * space, see __enable_fsgsbase(). Current Linux versions do not allow enabling
 * this instruction from user land, thus the need for this driver.
 */

#include <asm/tlbflush.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/version.h>
#include "gsgx.h"

#define DRV_DESCRIPTION "Graphene SGX Driver"
#define DRV_VERSION     "0.10"

MODULE_DESCRIPTION(DRV_DESCRIPTION);
MODULE_AUTHOR("Dmitrii Kuvaiskii <dmitrii.kuvaiskii@intel.com>");
MODULE_VERSION(DRV_VERSION);

static void __enable_fsgsbase(void* v) {
#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 0, 0)
    write_cr4(read_cr4() | X86_CR4_FSGSBASE);
#else
    cr4_set_bits(X86_CR4_FSGSBASE);
    __write_cr4(__read_cr4() | X86_CR4_FSGSBASE);
#endif
}

static void __disable_fsgsbase(void* v) {
#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 0, 0)
    write_cr4(read_cr4() & ~X86_CR4_FSGSBASE);
#else
    cr4_clear_bits(X86_CR4_FSGSBASE);
    __write_cr4(__read_cr4() & ~X86_CR4_FSGSBASE);
#endif
}

static const struct file_operations gsgx_fops = {
    .owner = THIS_MODULE
};

static struct miscdevice gsgx_dev = {
    .minor = GSGX_MINOR,
    .name  = "gsgx",
    .fops  = &gsgx_fops,
    .mode  = S_IRUGO | S_IWUGO,
};

static int gsgx_setup(void) {
    int ret;

    ret = misc_register(&gsgx_dev);
    if (ret) {
        pr_err("misc_register() failed\n");
        return ret;
    }

    on_each_cpu(__enable_fsgsbase, NULL, 1);

    return 0;
}

static void gsgx_teardown(void) {
    on_each_cpu(__disable_fsgsbase, NULL, 1);

    if (gsgx_dev.this_device)
        misc_deregister(&gsgx_dev);
}

static int __init gsgx_init(void) {
    int ret;

    pr_info(DRV_DESCRIPTION " v" DRV_VERSION "\n");

    if (!boot_cpu_has(X86_FEATURE_FSGSBASE)) {
        pr_err("FSGSBASE feature required by Graphene is not supported by this CPU!\n");
        return -ENODEV;
    }

    ret = gsgx_setup();
    if (ret) {
        gsgx_teardown();
        return ret;
    }

    return 0;
}

static void __exit gsgx_exit(void) {
    gsgx_teardown();
}

module_init(gsgx_init);
module_exit(gsgx_exit);
MODULE_LICENSE("GPL");
