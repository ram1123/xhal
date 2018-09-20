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

#ifndef TRACE
  #define TRACE(MSG) LOG4CPLUS_TRACE(m_gemLogger, MSG)
#endif
#ifndef DEBUG
  #define DEBUG(MSG) LOG4CPLUS_DEBUG(m_gemLogger, MSG)
#endif
#ifndef INFO
  #define INFO(MSG) LOG4CPLUS_INFO(m_gemLogger, MSG)
#endif
#ifndef WARN
  #define WARN(MSG) LOG4CPLUS_WARN(m_gemLogger, MSG)
#endif
#ifndef ERROR
  #define ERROR(MSG) LOG4CPLUS_ERROR(m_gemLogger, MSG)
#endif
#ifndef FATAL
  #define FATAL(MSG) LOG4CPLUS_FATAL(m_gemLogger, MSG)
#endif


#define STANDARD_CATCH \
	catch (wisc::RPCSvc::NotConnectedException &e) { \
		ERROR("Caught NotConnectedException: " << e.message.c_str()); \
    throw xhal::utils::XHALRPCNotConnectedException("RPC NotConnectedException: " + e.message);\
	} \
	catch (wisc::RPCSvc::RPCErrorException &e) { \
		ERROR("Caught RPCErrorException: " << e.message.c_str()); \
    throw xhal::utils::XHALRPCException("RPC ErrorException: " + e.message);\
	} \
	catch (wisc::RPCSvc::RPCException &e) { \
		ERROR("Caught exception: " << e.message.c_str()); \
    throw xhal::utils::XHALRPCException("RPC exception: " + e.message);\
	} \
  catch (wisc::RPCMsg::BadKeyException &e) { \
    ERROR("Caught exception: " << e.key.c_str()); \
    throw xhal::utils::XHALRPCException("RPC BadKeyException (most probably remote register not accessible): " + e.key);\
	} 

#define ASSERT(x) do { \
		if (!(x)) { \
			printf("Assertion Failed on line %u: %s\n", __LINE__, #x); \
      throw xhal::utils::XHALException("ASSERT failure");\
		} \
	} while (0)

namespace xhal {
  /**
   * @class XHALInterface
   * @brief Provides interface to call remote procedures at Zynq CPU 
   */
  class XHALInterface
  {
    public:
      /**
       * @brief Default constructor
       * @param board_domain_name domain name of CTP7
       */
      XHALInterface(const std::string& board_domain_name);
      /**
       * @brief Constructor, taking also the external logger
       * @param board_domain_name domain name of CTP7
       */
      XHALInterface(const std::string& board_domain_name, log4cplus::Logger& logger);

      virtual ~XHALInterface();

      /**
       * @brief Initialize interface and establish RPC service connection with CTP7
       */
      void connect();

      /**
       * @brief Reconnect to RPC service and reload required modules
       */
      inline virtual void reconnect(){this->connect();}

      /**
       * @brief Initialize interface and establish RPC service connection with CTP7
       */
      void disconnect();

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
      log4cplus::Logger m_gemLogger;
      wisc::RPCSvc rpc;
      wisc::RPCMsg req, rsp;
      bool isConnected;
      static int index;
  };
}
#endif  // XHALINTERFACE_H
