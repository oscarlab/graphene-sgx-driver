ifneq ($(KERNELRELEASE),)
	graphene-sgx-y := \
		gsgx_ioctl_1_6.o \
		gsgx_ioctl_1_7.o \
		gsgx_fsgsbase.o \
		gsgx_main.o
	obj-m += graphene-sgx.o
else
KDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

.PHONY: default
default: isgx_version.h linux-sgx-driver
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) CFLAGS_MODULE="-DDEBUG -g -O0" modules

install: default
	$(MAKE) INSTALL_MOD_DIR=kernel/drivers/graphene -C $(KDIR) M=$(PWD) modules_install
	sh -c "cat /etc/modules | grep -Fxq graphene_sgx || echo graphene_sgx >> /etc/modules"
	/sbin/depmod
	sh -c "cat /etc/rc.local | grep -Fxq \"sysctl vm.mmap_min_addr=0\" || sed -ie '/^exit 0/i sysctl vm.mmap_min_addr=0' /etc/rc.local"


.INTERMEDIATE: link-sgx-driver
link-sgx-driver:
	@./link-intel-driver.py

isgx_version.h linux-sgx-driver: link-sgx-driver

endif

.PHONY: clean
clean:
	rm -vrf linux-sgx-driver isgx_version.h
	rm -vrf *.o *.ko *.order *.symvers *.mod.c .tmp_versions .*o.cmd
