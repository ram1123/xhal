#include "xhal/utils/XHALXMLParser.h"
#include <iostream>
#include <string>

namespace xhal {
  namespace test {
    class parse_t
    {
      public:
        parse_t(const std::string & address_table_filename)
        {
          m_parser = new xhal::utils::XHALXMLParser(address_table_filename);
        }
        ~parse_t()
        {
          if (m_parser) delete m_parser;
        }
        int launch()
        {
          try 
          {
            m_parser->setLogLevel(2);
            m_parser->parseXML();
          } catch (...){
            std::cout << "Parsing failed" << std::endl;
            return 1;
          }
          std::cout << "Address table parsed successfully, now use getParser method to retrieve the parser handler" << std::endl;
          return 0;
        }
        xhal::utils::XHALXMLParser * getParser()
        {
          return m_parser;
        }
      private:
        xhal::utils::XHALXMLParser * m_parser;
    };
  }
}
