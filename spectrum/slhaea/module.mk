DIR          := slhaea
MODNAME      := slhaea

SLHAEA_HDR   := \
		$(DIR)/slhaea.h

SLHAEA_MK    := \
		$(DIR)/module.mk

SLHAEA_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

.PHONY:         all-$(MODNAME) clean-$(MODNAME) distclean-$(MODNAME)

all-$(MODNAME):

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(SLHAEA_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(SLHAEA_HDR) $(SLHAEA_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(SLHAEA_MK) $(SLHAEA_INSTALL_DIR)
endif

clean-$(MODNAME):

distclean-$(MODNAME): clean-$(MODNAME)

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)
