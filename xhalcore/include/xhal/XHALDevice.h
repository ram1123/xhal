/**
 * @file XHALDevice.h
 * Hardware device for XHAL
 *
 * @author Mykhailo Dalchenko
 * @version 1.0 
 */

#ifndef XHALDEVICE_H
#define XHALDEVICE_H

#include "xhal/utils/XHALXMLParser.h"
#include "xhal/XHALInterface.h"

#include <string>

namespace xhal {
  /**
   * @class XHALDevice
   * @brief provide interface to call remote procedures at Zynq CPU and basic FW registers manipulation
   */
  class XHALDevice : public XHALInterface
  {
    public:
      /**
       * @brief Default constructor
       *
       * Parses XML file
       * @param board_domain_name domain name of CTP7
       * @param address_table_filename XML address table file name
       */
      XHALDevice(const std::string& board_domain_name, const std::string& address_table_filename);

      /**
       * @brief read FW register by its name
       * applies reading mask if any
       */
      uint32_t readReg(std::string regName);
      /**
       * @brief read FW register by its address
       * reg mask is ignored!!
       */
      uint32_t readReg(uint32_t address);
      /**
       * @brief write FW register by its name
       * applies read/write mask if any
       */
      void writeReg(std::string regName, uint32_t value);
      //void writeReg(uint32_t address, uint32_t value);
    private:
      std::string m_address_table_filename;
      xhal::utils::XHALXMLParser * m_parser;
      xhal::utils::Node m_node;
  };
}
#endif  // XHALDEVICE_H
