.PHONY: default
default: sgx.h

sgx.h:
	@./link-intel-driver.py

.PHONY: clean
clean:

.PHONY: distclean
distclean: clean
	$(RM) sgx.h
