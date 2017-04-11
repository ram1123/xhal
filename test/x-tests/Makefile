ifndef PETA_STAGE
$(error "Error: PETA_STAGE environment variable not set.  Change to the root of your PetaLinux install, and source the settings.sh file")
endif
include ../../xcompile/apps.common.mk


IncludeDirs = ${XHAL_ROOT}/include
IncludeDirs += ${XHAL_ROOT}/xcompile/xerces-c-3.1.4/src
IncludeDirs += ${XHAL_ROOT}/xcompile/log4cplus-1.1.2/include
INC=$(IncludeDirs:%=-I%)

LDFLAGS+=-L${XHAL_ROOT}/lib

APP = parse_t

# Add any other object files to this list below
APP_OBJS = parse_t.o

all: build

build: $(APP)

$(APP): $(APP_OBJS)
	$(CXX) -std=c++14 $(CFLAGS) $(LDFLAGS) $(INC) -o $@ $(APP_OBJS) $(LDLIBS) -lmemsvc -lxhal -lxerces-c -llog4cplus

clean:
	-rm -f $(APP) *.elf *.gdb *.o


%.o: %.cpp
	$(CXX) -std=c++14 -c $(CFLAGS) $(INC) -o $@ $<

.PHONY: build
help:
	@echo ""
	@echo "Quick reference for various supported build targets for $(INSTANCE)."
	@echo "----------------------------------------------------"
	@echo "  clean                  clean out build objects"
	@echo "  all                    build $(INSTANCE)
	@echo "  build                  build subsystem"
