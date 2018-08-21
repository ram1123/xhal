/**
 * @file XHALInterface.h
 * Hardware interface for XHAL
 *
 * @author Mykhailo Dalchenko
 * @version 1.0 
 */

#ifndef XHALINTERFACE_H
#define XHALINTERFACE_H

#include <cstring>
#include <string>
#include "xhal/rpc/wiscrpcsvc.h"
#include "xhal/utils/Exception.h"

#include "log4cplus/logger.h"
#include "log4cplus/loglevel.h"
#include "log4cplus/loggingmacros.h"
#include "log4cplus/consoleappender.h"

#define TRACE(MSG) LOG4CPLUS_TRACE(m_logger, MSG)
#define DEBUG(MSG) LOG4CPLUS_DEBUG(m_logger, MSG)
#define INFO( MSG) LOG4CPLUS_INFO( m_logger, MSG)
#define WARN( MSG) LOG4CPLUS_WARN( m_logger, MSG)
#define ERROR(MSG) LOG4CPLUS_ERROR(m_logger, MSG)
#define FATAL(MSG) LOG4CPLUS_FATAL(m_logger, MSG)


#define STANDARD_CATCH \
	catch (wisc::RPCSvc::NotConnectedException &e) { \
		ERROR("Caught NotConnectedException: " << e.message.c_str()); \
    throw xhal::utils::Exception(strcat("RPC NotConnectedException: ", e.message.c_str()));\
	} \
	catch (wisc::RPCSvc::RPCErrorException &e) { \
		ERROR("Caught RPCErrorException: " << e.message.c_str()); \
    throw xhal::utils::Exception(strcat("RPC ErrorException: ", e.message.c_str()));\
	} \
	catch (wisc::RPCSvc::RPCException &e) { \
		ERROR("Caught exception: " << e.message.c_str()); \
    throw xhal::utils::Exception(strcat("RPC exception: ", e.message.c_str()));\
	} \
  catch (wisc::RPCMsg::BadKeyException &e) { \
    ERROR("Caught exception: " << e.key.c_str()); \
    throw xhal::utils::Exception(strcat("RPC BadKeyException (most probably remote register not accessible): ", e.key.c_str()));\
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
   * @brief provide interface to call remote procedures at Zynq CPU 
   */
  class XHALInterface
  {
    public:
      /**
       * @brief Default constructor
       * @param board_domain_name domain name of CTP7
       * @param address_table_filename XML address table file name
       */
      XHALInterface(const std::string& board_domain_name);
      ~XHALInterface();

      /**
       * @brief Initialize interface and establish RPC service connection with CTP7
       */
      void connect();
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

    protected:
      std::string m_board_domain_name;
      log4cplus::Logger m_logger;
      wisc::RPCSvc rpc;
      wisc::RPCMsg req, rsp;
  };
}
#endif  // XHALINTERFACE_H
