BUILD_HOME   := $(shell dirname `cd ../; pwd`)
Project      := xhal
Package      := xhal
ShortPackage := xhal
LongPackage  := xhalarm
PackageName  := $(ShortPackage)
PackagePath  := $(shell pwd)
PackageDir   := pkg/$(ShortPackage)
Packager     := Mykhailo Dalchenko
Arch         := arm

XHAL_VER_MAJOR:=$(shell $(BUILD_HOME)/$(Project)/config/tag2rel.sh | awk '{split($$0,a," "); print a[1];}' | awk '{split($$0,b,":"); print b[2];}')
XHAL_VER_MINOR:=$(shell $(BUILD_HOME)/$(Project)/config/tag2rel.sh | awk '{split($$0,a," "); print a[2];}' | awk '{split($$0,b,":"); print b[2];}')
XHAL_VER_PATCH:=$(shell $(BUILD_HOME)/$(Project)/config/tag2rel.sh | awk '{split($$0,a," "); print a[3];}' | awk '{split($$0,b,":"); print b[2];}')

INSTALL_PREFIX=/mnt/persistent/xhal

include $(BUILD_HOME)/$(Project)/config/mfCommonDefs.mk
include $(BUILD_HOME)/$(Project)/config/mfZynq.mk
include $(BUILD_HOME)/$(Project)/config/mfRPMRules.mk

ADDFLAGS=-std=gnu++14

IncludeDirs = $(BUILD_HOME)/$(Project)/xhalcore/include
INC=$(IncludeDirs:%=-I%)

Libraries+= -llog4cplus -lxerces-c -lstdc++

LDFLAGS+=-shared $(LibraryDirs)

SrcLocation =$(BUILD_HOME)/$(Project)/xhalcore/src/common
SRCS_XHAL   = $(shell echo $(SrcLocation)/utils/*.cpp)

## Place object files in lib/linux?
ObjLocation = src/linux/$(Arch)
OBJS_XHAL   = $(patsubst $(SrcLocation)/%,$(ObjLocation)/%, $(SRCS_XHAL:.cpp=.o))

XHAL_LIB=$(BUILD_HOME)/$(Project)/$(LongPackage)/lib/libxhal.so

.PHONY: clean rpc prerpm

default: build
	@echo "Running default target"
	$(MakeDir) $(PackageDir)

_rpmprep: preprpm
	@echo "Running _rpmprep target"

preprpm: default
	@echo "Running preprpm target"
	@cp -rf lib $(PackageDir)

build: clean $(XHAL_LIB)

_all: clean $(XHAL_LIB) 

doc:
	@echo "TO DO"

$(XHAL_LIB): $(OBJS_XHAL) 
	@mkdir -p $(BUILD_HOME)/$(Project)/$(LongPackage)/lib
	$(CC) $(ADDFLAGS) $(LDFLAGS) -o $@ $^ $(Libraries)

$(OBJS_XHAL): $(SRCS_XHAL)
	$(MakeDir) -p $(shell dirname $@)
	$(CC) $(CFLAGS) $(ADDFLAGS) $(INC) -c -o $@ $<

%.o: %.c
	$(CC) -std=gnu99 -c $(CFLAGS) -o $@ $<
%.o: %.cc
	$(CXX) -std=c++0x -c $(CFLAGS) -o $@ $<

clean:
	-rm -rf $(OBJS_XHAL)
	-rm -rf $(XHAL_LIB)
	-rm -rf $(BUILD_HOME)/$(Project)/$(LongPackage)/lib
	-rm -rf $(PackageDir)

cleandoc: 
	@echo "TO DO"
