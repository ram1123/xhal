#include "xhal/rpc/calibration_routines.h"

DLLEXPORT uint32_t ttcGenToggle(uint32_t ohN, bool bRun){
    wisc::RPCSvc* rpc_loc = getRPCptr();
    req = wisc::RPCMsg("calibration_routines.ttcGenToggle");
    req.set_word("ohN", ohN);
    req.set_word("bRun", bRun);
    try {
        rsp = rpc_loc->call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        return 1;
    }
    return 0;
} //End ttcGenToggle(...)

/***
 * @brief configure TTC generator
 */
DLLEXPORT uint32_t ttcGenConf(uint32_t ohN, uint32_t mode, uint32_t type, uint32_t pulseDelay, uint32_t L1Ainterval, uint32_t nPulses, bool bRun)
{
    wisc::RPCSvc* rpc_loc = getRPCptr();
    //wisc::RPCMsg req_loc, rsp_loc;
    //req_loc = wisc::RPCMsg("calibration_routines.ttcGenConf");
    req = wisc::RPCMsg("calibration_routines.ttcGenConf");
    req.set_word("ohN", ohN);
    req.set_word("mode", mode);
    req.set_word("type", type);
    req.set_word("pulseDelay", pulseDelay);
    req.set_word("L1Ainterval", L1Ainterval);
    req.set_word("nPulses", nPulses);
    req.set_word("bRun", bRun);
    try {
        rsp = rpc_loc->call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        return 1;
    }
    return 0;
}

/***
 * @brief run a generic scan routine
 */
DLLEXPORT uint32_t genScan(uint32_t nevts, uint32_t ohN, uint32_t dacMin, uint32_t dacMax, uint32_t dacStep, uint32_t ch, uint32_t enCal, uint32_t mask, char * scanReg, bool useUltra, uint32_t * result)
{
    req = wisc::RPCMsg("calibration_routines.genScan");

    req.set_word("nevts", nevts);
    req.set_word("ohN", ohN);
    req.set_word("dacMin", dacMin);
    req.set_word("dacMax", dacMax);
    req.set_word("dacStep", dacStep);
    req.set_word("ch", ch);
    req.set_word("enCal", enCal);
    req.set_word("mask", mask);
    if(useUltra){
        req.set_word("useUltra", useUltra);
    }
    req.set_string("scanReg", std::string(scanReg));

    wisc::RPCSvc* rpc_loc = getRPCptr();

    try {
        rsp = rpc_loc->call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        printf("Caught an error: %s\n", (rsp.get_string("error")).c_str());
        return 1;
    }
    const uint32_t size = (dacMax - dacMin+1)*24/dacStep;
    if (rsp.get_key_exists("data")) {
        ASSERT(rsp.get_word_array_size("data") == size);
        rsp.get_word_array("data", result);
    } else {
        printf("No data key found");
        return 1;
    }

    return 0;
}
