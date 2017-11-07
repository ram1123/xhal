#ifndef CALIBRATION_ROUTINES_H
#define CALIBRATION_ROUTINES_H

#include "xhal/rpc/utils.h"

DLLEXPORT uint32_t ttcGenToggle(uint32_t ohN, bool enable);
DLLEXPORT uint32_t ttcGenConf(uint32_t ohN, uint32_t mode, uint32_t type, uint32_t pulseDelay,
        uint32_t L1Ainterval, uint32_t nPulses, bool enable);
DLLEXPORT uint32_t genScan(uint32_t nevts, uint32_t ohN, uint32_t dacMin, uint32_t dacMax, uint32_t dacStep,
        uint32_t ch, uint32_t enCal, uint32_t mask, char * scanReg, bool useUltra, uint32_t * result);

#endif
