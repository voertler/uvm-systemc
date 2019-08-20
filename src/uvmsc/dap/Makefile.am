include $(top_srcdir)/config/Make-rules

H_FILES = \
	uvm_dap.h \
	uvm_get_to_lock_dap.h \
	uvm_set_before_get_dap.h \
	uvm_set_get_dap_base.h \
	uvm_simple_lock_dap.h

NO_H_FILES = 

noinst_HEADERS = $(H_FILES)

CXX_FILES = 

NO_CXX_FILES =

noinst_LTLIBRARIES = libdap.la

libdap_la_SOURCES = $(H_FILES) $(NO_H_FILES) $(CXX_FILES)

INCLUDE_DIR = $(prefix)/include/uvmsc/dap

install-data-local:
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(INCLUDE_DIR)
	for file in $(noinst_HEADERS); do \
	  $(INSTALL_DATA) $(srcdir)/$$file $(DESTDIR)$(INCLUDE_DIR)/$$file; \
	done

uninstall-local:
	@$(NORMAL_UNINSTALL)
	for file in $(noinst_HEADERS); do \
	  rm -f $(DESTDIR)$(INCLUDE_DIR)/$$file; \
	done
	-rmdir $(DESTDIR)$(INCLUDE_DIR)

## Taf!
