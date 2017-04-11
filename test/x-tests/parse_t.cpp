#include "xhal/utils/XHALXMLParser.h"
#include <iostream>
#include <string>

int main()
{
   xhal::utils::XHALXMLParser * m_parser = new xhal::utils::XHALXMLParser("/mnt/persistent/texas/gem_amc_top.xml");
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
