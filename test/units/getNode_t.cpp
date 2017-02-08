#include "xhal/utils/XHALXMLParser.h"
#include <iostream>

namespace xhal {
  namespace utils {
  }
  namespace test {
    class getNode_t
    {
      public:
        getNode_t(xhal::utils::XHALXMLParser * parser)
        {
          m_parser = parser;
        }
        ~getNode_t(){}
        int launch()
        {
          if (auto myOptNode = m_parser->getNode("top.GEM_SYSTEM.BOARD_ID"))
          {
            myNode = myOptNode.value();
            std::cout << "Test called for incomplete node name top.GEM_SYSTEM.BOARD_ID  and returned: " << std::endl; 
            std::cout << "Node name: " << myNode.name << ", Node address: " << std::hex << myNode.address << std::dec << std::endl;
            return 1;
          }
          if (auto myOptNode = m_parser->getNode("top.GEM_AMC.GEM_SYSTEM.BOARD_ID"))
          {
            myNode = myOptNode.value();
            if ((myNode.name == "top.GEM_AMC.GEM_SYSTEM.BOARD_ID") && (myNode.address == 0x00900002))
            {
              return 0;
            }
          } else {
            std::cout << "Test called for node top.GEM_AMC.GEM_SYSTEM.BOARD_ID with address 0x00900002 and returned: " << std::endl; 
            std::cout << "Node name: " << myNode.name << ", Node address: " << std::hex << myNode.address << std::dec << std::endl;
            return 1;
          }
        }
      private:
        xhal::utils::XHALXMLParser * m_parser;
        xhal::utils::Node myNode;
    };
  }
}
