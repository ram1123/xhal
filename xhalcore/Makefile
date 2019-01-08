BUILD_HOME   := $(shell dirname `cd ../; pwd`)
Project      := xhal
Package      := xhal
ShortPackage := xhal
LongPackage  := xhalcore
PackageName  := $(ShortPackage)
PackagePath  := $(shell pwd)
PackageDir   := pkg/$(ShortPackage)
Packager     := Mykhailo Dalchenko
Arch         := x86_64

XHAL_VER_MAJOR:=$(shell $(BUILD_HOME)/$(Project)/config/tag2rel.sh | awk '{split($$0,a," "); print a[1];}' | awk '{split($$0,b,":"); print b[2];}')
XHAL_VER_MINOR:=$(shell $(BUILD_HOME)/$(Project)/config/tag2rel.sh | awk '{split($$0,a," "); print a[2];}' | awk '{split($$0,b,":"); print b[2];}')
XHAL_VER_PATCH:=$(shell $(BUILD_HOME)/$(Project)/config/tag2rel.sh | awk '{split($$0,a," "); print a[3];}' | awk '{split($$0,b,":"); print b[2];}')

include $(BUILD_HOME)/$(Project)/config/mfCommonDefs.mk
include $(BUILD_HOME)/$(Project)/config/mfPythonDefs.mk
include $(BUILD_HOME)/$(Project)/config/mfRPMRules.mk

CCFLAGS=-O0 -g3 -fno-inline -Wall -pthread
ADDFLAGS=-fPIC -std=c++11 -m64

IncludeDirs+= /opt/xdaq/include
IncludeDirs+= $(BUILD_HOME)/$(Project)/$(LongPackage)/include
INC=$(IncludeDirs:%=-I%)

Libraries+= -llog4cplus -lxerces-c -lwiscrpcsvc -lstdc++

LibraryDirs+=-L/opt/xdaq/lib
LibraryDirs+=-L/opt/wiscrpcsvc/lib

LDFLAGS = -shared $(LibraryDirs)

SrcLocation  = src/common
SRCS_UTILS   = $(shell echo $(SrcLocation)/utils/*.cpp)
SRCS_XHAL    = $(shell echo $(SrcLocation)/*.cpp)
SRCS_XHALPY  = $(shell echo $(SrcLocation)/python_wrappers/*.cpp)
SRCS_RPC_MAN = $(shell echo $(SrcLocation)/rpc_manager/*.cpp)

## Place object files in src/linux/$(Arch)
ObjLocation = src/linux/$(Arch)
OBJS_UTILS   = $(patsubst $(SrcLocation)/%,$(ObjLocation)/%, $(SRCS_UTILS:.cpp=.o))
OBJS_XHAL    = $(patsubst $(SrcLocation)/%,$(ObjLocation)/%, $(SRCS_XHAL:.cpp=.o))
OBJS_XHALPY  = $(patsubst $(SrcLocation)/%,$(ObjLocation)/%, $(SRCS_XHALPY:.cpp=.o))
OBJS_RPC_MAN = $(patsubst $(SrcLocation)/%,$(ObjLocation)/%, $(SRCS_RPC_MAN:.cpp=.o))

XHALCORE_LIB = $(BUILD_HOME)/$(Project)/$(LongPackage)/lib/libxhal.so
RPC_MAN_LIB  = $(BUILD_HOME)/$(Project)/$(LongPackage)/lib/librpcman.so
XHALPY_LIB   = $(BUILD_HOME)/$(Project)/$(LongPackage)/lib/xhalpy.so

.PHONY: clean xhalcore rpc prerpm

default: build
	@echo "Running default target"
	$(MakeDir) $(PackageDir)

_rpmprep: preprpm
	@echo "Running _rpmprep target"

preprpm: default
	@echo "Running preprpm target"
	$(MakeDir) lib/arm
	@cp -rfp $(BUILD_HOME)/$(Project)/xhalarm/lib/*.so lib/arm
	@cp -rfp lib $(PackageDir)

build: xhalcore rpc

_all: $(XHALCORE_LIB) $(RPC_MAN_LIB) $(XHALPY_LIB)

rpc: xhalcore $(RPC_MAN_LIB)

xhalcore: $(XHALCORE_LIB)

xhalpy: xhalcore rpc $(XHALPY_LIB)

doc:
	@echo "TO DO"

$(OBJS_UTILS): $(SRCS_UTILS)
	@rm -rf $(OBJS_UTILS)
	$(MakeDir) $(shell dirname $@)
	$(CC) $(CCFLAGS) $(ADDFLAGS) $(INC) -c $< -o $@

$(OBJS_XHAL): $(SRCS_XHAL)
	$(MakeDir) $(shell dirname $@)
#	$(CC) $(CCFLAGS) $(ADDFLAGS) $(INC) $(Libraries) -c $(@:%.o=%.cpp) -o $@ 
	$(CC) $(CCFLAGS) $(ADDFLAGS) $(INC) -c -o $@ $(patsubst $(ObjLocation)/%,$(SrcLocation)/%, $(@:%.o=%.cpp))

$(OBJS_RPC_MAN): $(SRCS_RPC_MAN)
	$(MakeDir) $(shell dirname $@)
#	$(CC) $(CCFLAGS) $(ADDFLAGS) $(INC) $(Libraries) -c $(@:%.o=%.cpp) -o $@ 
	$(CC) $(CCFLAGS) $(ADDFLAGS) $(INC) -c -o $@ $(patsubst $(ObjLocation)/%,$(SrcLocation)/%, $(@:%.o=%.cpp))

$(OBJS_XHALPY):$(SRCS_XHALPY)
	$(MakeDir) $(shell dirname $@)
	$(CC) $(CCFLAGS) $(ADDFLAGS) $(INC) -I$(PYTHON_INCLUDE_PREFIX) -c $< -o $@

$(XHALCORE_LIB): $(OBJS_UTILS) $(OBJS_XHAL)
	$(MakeDir) $(BUILD_HOME)/$(Project)/$(LongPackage)/lib
	$(CC) $(ADDFLAGS) $(LDFLAGS) -o $@ $^ $(Libraries)

$(RPC_MAN_LIB): $(OBJS_RPC_MAN)
	$(MakeDir) $(BUILD_HOME)/$(Project)/$(LongPackage)/lib
	$(CC) $(ADDFLAGS) $(LDFLAGS) -o $@ $^ $(Libraries)

$(XHALPY_LIB): $(OBJS_XHALPY)
	$(MakeDir) $(BUILD_HOME)/$(Project)/$(LongPackage)/lib
	$(CC) $(ADDFLAGS) $(LDFLAGS) -L$(PYTHON_LIB_PREFIX) -Llib -o $@ $< $(Libraries) -lboost_python -l$(PYTHON_LIB) -lxhal -lrpcman

clean:
	-rm -rf $(OBJS_UTILS) $(OBJS_XHAL) $(OBJS_RPC_MAN) $(OBJS_XHALPY)
	-rm -rf $(XHALCORE_LIB) $(XHALPY_LIB) $(RPC_MAN_LIB)
	-rm -rf $(BUILD_HOME)/$(Project)/$(LongPackage)/lib
	-rm -rf $(PackageDir)

cleandoc: 
	@echo "TO DO"
