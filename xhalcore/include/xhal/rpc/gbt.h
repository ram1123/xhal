#ifndef GBT_H
#define GBT_H

#include "xhal/rpc/utils.h"

DLLEXPORT uint32_t scanGBTPhases(uint32_t ohN, uint32_t N, uint32_t phaseMin, uint32_t phaseMax, uint32_t phaseStep, uint32_t *results);
DLLEXPORT uint32_t writeGBTConfig(uint32_t ohN, uint32_t gbtN, uint32_t configSize, uint8_t *config);
DLLEXPORT uint32_t writeGBTPhase(uint32_t ohN, uint32_t vfatN, uint8_t phase);

#endif

