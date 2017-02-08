/**
 * @file XHALInterface.h
 * Hardware interface for XHAL
 *
 * @author Mykhailo Dalchenko
 * @version 1.0 
 */

#ifndef XHALINTERFACE_H
#define XHALINTERFACE_H

#include <string>
#include "xhal/rpc/librpcsvc.h"
#include "xhal/utils/XHALXMLParser.h"
#include "xhal/utils/Exception.h"

#define STANDARD_CATCH \
	catch (RPCSvc::NotConnectedException &e) { \
		ERROR("Caught NotConnectedException: " << e.message.c_str()); \
    throw xhal::utils::Exception(strcat("RPC exception: ", e.message.c_str()));\
	} \
	catch (RPCSvc::RPCErrorException &e) { \
		ERROR("Caught RPCErrorException: " << e.message.c_str()); \
    throw xhal::utils::Exception(strcat("RPC exception: ", e.message.c_str()));\
	} \
	catch (RPCSvc::RPCException &e) { \
		ERROR("Caught exception: " << e.message.c_str()); \
    throw xhal::utils::Exception(strcat("RPC exception: ", e.message.c_str()));\
	} \
  catch (RPCMsg::BadKeyException &e) { \
    ERROR("Caught exception: " << e.key.c_str()); \
    throw xhal::utils::Exception(strcat("RPC exception (most probably remote register not accessible): ", e.key.c_str()));\
	} 

#define ASSERT(x) do { \
		if (!(x)) { \
			printf("Assertion Failed on line %u: %s\n", __LINE__, #x); \
      throw xhal::utils::Exception("ASSERT failure");\
		} \
	} while (0)

namespace xhal {
  /**
   * @class XHALInterface
   * @brief provide interface to call remote procedures at Zynq CPU and basic FW registers manipulation
   */
  class XHALInterface
  {
    public:
      /**
       * @brief Default constructor
       * @param board_domain_name domain name of CTP7
       * @param address_table_filename XML address table file name
       */
      XHALInterface(const std::string& board_domain_name, const std::string& address_table_filename);
      ~XHALInterface(){}

      /**
       * @brief Initialize interface and establish RPC service connection with CTP7
       *
       * Parses XML file and starts the RPCSvc connection
       */
      void init();
      /**
       * @brief load remote module
       */
      void loadModule(const std::string& module_name, const std::string& module_version);

      /**
       * @brief sets amount of logging/debugging information to display
       * @param loglevel:
       * 0 - ERROR
       * 1 - WARN
       * 2 - INFO
       * 3 - DEBUG
       * 4 - TRACE
       */
      void setLogLevel(int loglevel);

      /**
       * @brief read FW register by its name
       */
      uint32_t readReg(std::string regName);
      /**
       * @brief read FW register by its address
       */
      uint32_t readReg(uint32_t address);
      //void writeReg(std::string regName, uint32_t value);
      //void writeReg(uint32_t address, uint32_t value);
    private:
      std::string m_board_domain_name;
      std::string m_address_table_filename;
      xhal::utils::XHALXMLParser * m_parser;
      xhal::utils::Node m_node;
      log4cplus::Logger m_logger;
      RPCSvc rpc;
      RPCMsg req, rsp;
  };
}
#endif  // XHALINTERFACE_H
