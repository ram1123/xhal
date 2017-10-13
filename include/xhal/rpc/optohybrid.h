#ifndef OPTOHYBRID_H
#define OPTOHYBRID_H

#include "xhal/rpc/utils.h"

DLLEXPORT uint32_t broadcastRead(uint32_t ohN, char * regName, uint32_t vfatMask, uint32_t * result);
DLLEXPORT uint32_t broadcastWrite(uint32_t ohN, char * regName, uint32_t value, uint32_t vfatMask);

#endif
