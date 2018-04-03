#include <array>
#include "xhal/rpc/vfat3.h"

/***
 * @brief load configuration parameters to VFAT3 chips
 */
DLLEXPORT uint32_t configureVFAT3s(uint32_t ohN, uint32_t vfatMask)
{
    req = wisc::RPCMsg("vfat3.configureVFAT3s");

    req.set_word("vfatMask",vfatMask);
    req.set_word("ohN",ohN);
    wisc::RPCSvc* rpc_loc = getRPCptr();

    try {
        rsp = rpc_loc->call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        printf("Caught an error: %s\n", (rsp.get_string("error")).c_str());
        return 1;
    }
    return 0;
}

/*! \fn DLLEXPORT uint32_t setChannelRegistersVFAT3(uint32_t ohN, uint32_t vfatMask, uint32_t *calEnable, uint32_t *masks, uint32_t *trimARM, uint32_t *trimARMPol, uint32_t *trimZCC, uint32_t *trimZCCPol)
 *  \brief sets all vfat3 channel registers
 *  \param ohN Optohybrid optical link number
 *  \param vfatMask Bitmask of chip positions determining which chips to use
 *  \param calEnable array pointer for calEnable with 3072 entries, the (vfat,chan) pairing determines the array index via: idx = vfat*128 + chan
 *  \param masks as calEnable but for channel masks
 *  \param trimARM as calEnable but for arming comparator trim value
 *  \param trimARMPol as calEnable but for arming comparator trim polarity
 *  \param trimZCC as calEnable but for zero crossing comparator trim value
 *  \param trimZCCPol as calEnable but for zero crossing comparator trim polarity
 */
DLLEXPORT uint32_t setChannelRegistersVFAT3(uint32_t ohN, uint32_t vfatMask, uint32_t *calEnable, uint32_t *masks, uint32_t *trimARM, uint32_t *trimARMPol, uint32_t *trimZCC, uint32_t *trimZCCPol){
    req = wisc::RPCMsg("vfat3.setChannelRegistersVFAT3");

    req.set_word("vfatMask",vfatMask);
    req.set_word("ohN",ohN);

    req.set_word_array("calEnable",calEnable,3072);
    req.set_word_array("masks",masks,3072);
    req.set_word_array("trimARM",masks,3072);
    req.set_word_array("trimARMPol",masks,3072);
    req.set_word_array("trimZCC",masks,3072);
    req.set_word_array("trimZCCPol",masks,3072);

    wisc::RPCSvc* rpc_loc = getRPCptr();

    try {
        rsp = rpc_loc->call_method(req);
    }
    STANDARD_CATCH;

    if (rsp.get_key_exists("error")) {
        printf("Caught an error: %s\n", (rsp.get_string("error")).c_str());
        return 1;
    }
    return 0;
}
