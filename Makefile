OUTDIR = bin
SRCDIR = $(CURDIR)/src

SRCS += \
	$(SRCDIR)/main.c

NXDK_DIR = $(CURDIR)/deps/nxdk
NXDK_NET = y
NXDK_SDL = y
# NXDK_CXX = y

ifeq ($(OUTPUT_DIR),)
OUTPUT_DIR = $(OUTDIR)
endif

XBE_TITLE = ClearCache
XISO_NAME = clear-cache
GEN_XISO = $(XISO_NAME).iso

CFLAGS += \
	$(addprefix -I,$(CURDIR)) \
	-D XBOX \
	-D OVERRIDE_640_X_480 #	only use 640x480 for now

ifeq ($(DEBUG),y)
CFLAGS += \
	$(addprefix -D,DEBUG)
endif

include $(NXDK_DIR)/Makefile
