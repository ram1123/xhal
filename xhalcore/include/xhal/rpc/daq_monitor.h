#ifndef DAQ_MONITOR_H
#define DAQ_MONITOR_H

#include "xhal/XHALInterface.h"

namespace xhal {
  namespace rpc {
    /**
    * @class DaqMonitor
    * @brief Provides interface to call remote utility methods 
    */
    class DaqMonitor : public XHALInterface
    {
      public:
        /**
         * @brief Default constructor
         *
         * Loads the neccessary remote modules
         * @param board_domain_name domain name of CTP7
         */
        DaqMonitor(const std::string& board_domain_name):xhal::XHALInterface(board_domain_name){this->loadModule("amc", "amc v1.0.1");}

        ~DaqMonitor(){}

        /**
         * @brief get an array of values for TTC main monitoring table
         *
         * @param result An array of monitoring values
         */
        uint32_t getmonTTCmain(uint32_t* result);

        /**
         * @brief get an array of values for TRIGGER main monitoring table
         *
         * @param result An array of monitoring values
         * @param noh Number of expected optical links, default value 12
         */
        uint32_t getmonTRIGGERmain(uint32_t* result, uint32_t noh = 12);

        /**
         * @brief get an array of values for TRIGGER OH main monitoring table
         *
         * @param result An array of monitoring values
         * @param noh Number of expected optical links, default value 12
         */
        uint32_t getmonTRIGGEROHmain(uint32_t* result, uint32_t noh = 12);

        /**
         * @brief get an array of values for DAQ main monitoring table
         *
         * @param result An array of monitoring values
         */
        uint32_t getmonDAQmain(uint32_t* result);

        /**
         * @brief get an array of values for DAQ OH main monitoring table
         *
         * @param result An array of monitoring values
         * @param noh Number of expected optical links, default value 12
         */
        uint32_t getmonDAQOHmain(uint32_t* result, uint32_t noh = 12);

        /**
         * @brief get an array of values for OH main monitoring table
         *
         * @param result An array of monitoring values
         * @param noh Number of expected optical links, default value 12
         */
        uint32_t getmonOHmain(uint32_t* result, uint32_t noh = 12);
    };
  }
}

#endif
