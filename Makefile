ifneq ($(KERNELRELEASE),)
	obj-m += gsgx.o
else
KDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

.PHONY: default
default: sgx.h
	$(MAKE) -C $(KDIR) M=$(PWD) CFLAGS_MODULE="-DDEBUG -g -O0" modules

sgx.h:
	@./link-intel-driver.py
endif

.PHONY: clean
clean:
	$(RM) -r *.o *.ko *.order *.symvers *.mod.c .tmp_versions .*o.cmd .cache.mk *.o.ur-safe

.PHONY: distclean
distclean: clean
	$(RM) sgx.h
