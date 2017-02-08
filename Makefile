CC=g++
CCFLAGS=-O0 -g3 -fno-inline -Wall -fPIC -pthread -m64
ADDFLAGS=-std=gnu++14

IncludeDirs = /opt/xdaq/include
IncludeDirs += /opt/rh/devtoolset-6/root/usr/include
IncludeDirs += ${XHAL_ROOT}/include
INC=$(IncludeDirs:%=-I%)

Libraries+= -llog4cplus -lxerces-c 
LibraryDirs+=-L/opt/xdaq/lib
LibraryDirs+=-L${XHAL_ROOT}/lib
LIB=$(LibraryDirs)
LIB+= $(Libraries)

LDFLAGS= -shared
SRCS = $(shell echo src/common/utils/*.cpp)
SRCS_XHAL = $(shell echo src/common/*.cpp)
OBJS = $(SRCS:.cpp=.o)
OBJS_XHAL = $(SRCS_XHAL:.cpp=.o)

SRCS_TEST = test/main_test.cpp
OBJS_TEST = $(SRCS_TEST:.cpp=.o)

TARGET_LIB=lib/libxhal.so
TARGET_TEST=test/bin/test

all:${TARGET_LIB} ${TARGET_TEST}

utils:${TARGET_LIB}

$(TARGET_LIB): $(OBJS) $(OBJS_XHAL)
	    $(CC) $(CCFLAGS) $(ADDFLAGS) ${LDFLAGS} $(INC) $(LIB) -lrpcsvc -o $@ $^

#$(SRCS:.cpp=.d):%.d:%.cpp
$(OBJS):$(SRCS)
	    $(CC) $(CCFLAGS) $(ADDFLAGS) $(INC) $(LIB) -c -o $@ $<

$(OBJS_XHAL):$(SRCS_XHAL)
	    $(CC) $(CCFLAGS) $(ADDFLAGS) $(INC) $(LIB) -c -o $@ $<

test:${TARGET_TEST}
$(TARGET_TEST): $(OBJS_TEST)
	    $(CC) $(CCFLAGS) $(ADDFLAGS) $(INC) $(LIB) -lxhal -lrpcsvc -o $@ $^

$(OBJS_TEST):$(SRCS_TEST)
	    $(CC) $(CCFLAGS) $(ADDFLAGS) $(INC) $(LIB) -lxhal -c -o $@ $<

.PHONY: clean
clean:
	    -${RM} ${TARGET_LIB} ${OBJS} ${OBJS_XHAL} ${TARGET_TEST} ${OBJS_TEST}



