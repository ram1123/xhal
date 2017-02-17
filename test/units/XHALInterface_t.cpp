#include "xhal/XHALInterface.h"
#include <iostream>

namespace xhal {
  namespace utils {
  }
  namespace test {
    class XHALInterface_t
    {
      public:
        XHALInterface_t(const std::string& board_domain_name, const std::string& address_table_filename)
        {
          s1 = board_domain_name; 
          s2 = address_table_filename;
          m_interface = new xhal::XHALInterface(s1, s2);
        }
        void init_t()
        {
          m_interface->init();
          //m_interface->setLogLevel(3);
        }
        void loadModule_t()
        {
          m_interface->loadModule("memory", "memory v1.0.1");
        }
        void readRegByName_t()
        {
          uint32_t res = m_interface->readReg("top.GEM_AMC.GEM_SYSTEM.BOARD_ID");
          //std::cout << "Read register top.GEM_AMC.GEM_SYSTEM.BOARD_ID: " << std::hex << res << std::dec << std::endl;
        }
        void writeReg_only_t()
        {
          m_interface->writeReg("top.GEM_AMC.GEM_SYSTEM.GBT.TX_SYNC_PATTERN", 0xbeef);
        }
        void writeReg_complete_test_t()
        {
          uint32_t test;
          test = m_interface->readReg("top.GEM_AMC.GEM_SYSTEM.GBT.TX_SYNC_PATTERN");
          std::cout << "Initial value of top.GEM_AMC.GEM_SYSTEM.GBT.TX_SYNC_PATTERN: " << std::hex << test << std::dec << std::endl;
          m_interface->writeReg("top.GEM_AMC.GEM_SYSTEM.GBT.TX_SYNC_PATTERN", 0x76bc);
          test = m_interface->readReg("top.GEM_AMC.GEM_SYSTEM.GBT.TX_SYNC_PATTERN");
          std::cout << "Value after write of top.GEM_AMC.GEM_SYSTEM.GBT.TX_SYNC_PATTERN: " << std::hex << test << std::dec << std::endl;
        }
      private:
        xhal::XHALInterface * m_interface;
        std::string s1,s2;
    };
  }
}
