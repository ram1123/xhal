BUILD_HOME   := $(shell dirname `cd ../; pwd`)
Project      := xhal
Package      := xhalcore
ShortPackage := xhalcore
LongPackage  := xhalcore
PackageName  := $(ShortPackage)
PackagePath  := $(shell pwd)
PackageDir   := pkg/$(ShortPackage)
Packager     := Mykhailo Dalchenko

XHALCORE_VER_MAJOR=1
XHALCORE_VER_MINOR=0
XHALCORE_VER_PATCH=0

include $(BUILD_HOME)/$(Project)/config/mfCommonDefs.mk
include $(BUILD_HOME)/$(Project)/config/mfRPMRules.mk

CC=g++
CCFLAGS=-O0 -g3 -fno-inline -Wall -fPIC -pthread -m64
ADDFLAGS=-std=gnu++14

IncludeDirs= /opt/xdaq/include
IncludeDirs+= /opt/rh/devtoolset-6/root/usr/include
IncludeDirs+= ${BUILD_HOME}/${Project}/${Package}/include
INC=$(IncludeDirs:%=-I%)

Libraries+= -llog4cplus -lxerces-c -lwiscrpcsvc
LibraryDirs+=-L/opt/xdaq/lib
LibraryDirs+=-L/opt/wiscrpcsvc/lib
LIB=$(LibraryDirs)
LIB+= $(Libraries)

LDFLAGS= -shared
SRCS_UTILS = $(shell echo src/common/utils/*.cpp)
SRCS_XHAL = $(shell echo src/common/*.cpp)
OBJS_UTILS = $(SRCS_UTILS:.cpp=.o)
OBJS_XHAL = $(SRCS_XHAL:.cpp=.o)
SRCS_RPC_MAN = $(shell echo src/common/rpc_manager/*.cc)
OBJS_RPC_MAN = $(SRCS_RPC_MAN:.cc=.o)

XHALCORE_LIB=${BUILD_HOME}/${Project}/${Package}/lib/libxhal.so
RPC_MAN_LIB=${BUILD_HOME}/${Project}/${Package}/lib/librpcman.so

.PHONY: clean xhalcore rpc prerpm

default:
	@echo "Running default target"
	$(MakeDir) $(PackageDir)

_rpmprep: preprpm
	@echo "Running _rpmprep target"
preprpm: default
	@echo "Running preprpm target"
	@cp -rf lib $(PackageDir)

build: xhalcore rpc

_all:${XHALCORE_LIB} ${RPC_MAN_LIB} 

rpc:${RPC_MAN_LIB}

xhalcore:${XHALCORE_LIB}

$(XHALCORE_LIB): $(OBJS_UTILS) $(OBJS_XHAL)
	@mkdir -p ${BUILD_HOME}/${Project}/${Package}/lib/
	$(CC) $(CCFLAGS) $(ADDFLAGS) ${LDFLAGS} $(INC) $(LIB) -o $@ $^

$(OBJS_UTILS):$(SRCS_UTILS)
	    $(CC) $(CCFLAGS) $(ADDFLAGS) $(INC) $(LIB) -c -o $@ $<

$(OBJS_XHAL):$(SRCS_XHAL)
	    $(CC) $(CCFLAGS) $(ADDFLAGS) $(INC) $(LIB) -c -o $@ $<

$(RPC_MAN_LIB): $(OBJS_RPC_MAN)
	$(CC) $(CCFLAGS) $(ADDFLAGS) ${LDFLAGS} $(INC) $(LIB) -o $@ $^

$(OBJS_RPC_MAN):$(SRCS_RPC_MAN)
	$(CC) $(CCFLAGS) $(ADDFLAGS) $(INC) $(LIB) -c $(@:%.o=%.cc) -o $@ 

clean:
	-${RM} ${XHALCORE_LIB} ${OBJS_UTILS} ${OBJS_XHAL} ${RPC_MAN_LIB} ${OBJS_RPC_MAN}
	-rm -rf $(PackageDir)

cleandoc: 
	@echo "TO DO"
