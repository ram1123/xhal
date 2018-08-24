#include "xhal/XHALInterface.h"

xhal::XHALInterface::XHALInterface(const std::string& board_domain_name):
  m_board_domain_name(board_domain_name)
{
  log4cplus::SharedAppenderPtr myAppender(new log4cplus::ConsoleAppender());
  std::auto_ptr<log4cplus::Layout> myLayout = std::auto_ptr<log4cplus::Layout>(new log4cplus::TTCCLayout());
  myAppender->setLayout( myLayout );
  // Following strange construction is required because it looks like log4cplus was compiled withot c++11 support...
  auto t_logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("XHALInterface"));
  m_logger = t_logger;
  m_logger.addAppender(myAppender);
  m_logger.setLogLevel(log4cplus::INFO_LOG_LEVEL);
  INFO("XHAL Logger tuned up");
  this->connect();
  INFO("XHAL Interface connected");
}

xhal::XHALInterface::~XHALInterface()
{
  m_logger.shutdown();
}

void xhal::XHALInterface::connect()
{
  try {
    rpc.connect(m_board_domain_name);
  }
  catch (wisc::RPCSvc::ConnectionFailedException &e) {
    ERROR("Caught RPCErrorException: " << e.message.c_str());
    throw xhal::utils::Exception(strcat("RPC ConnectionFailedException: ",e.message.c_str()));
  }
  catch (wisc::RPCSvc::RPCException &e) {
    ERROR("Caught exception: " << e.message.c_str());
    throw xhal::utils::Exception(strcat("RPC exception: ",e.message.c_str()));
  }
}

void xhal::XHALInterface::loadModule(const std::string& module_name, const std::string& module_version)
{
  try {
    ASSERT(rpc.load_module(module_name, module_version));
  }
  STANDARD_CATCH;
}

void xhal::XHALInterface::setLogLevel(int loglevel)
{
  switch(loglevel)
  {
    case 0:
      m_logger.setLogLevel(log4cplus::ERROR_LOG_LEVEL);
      break;
    case 1:
      m_logger.setLogLevel(log4cplus::WARN_LOG_LEVEL);
      break;
    case 2:
      m_logger.setLogLevel(log4cplus::INFO_LOG_LEVEL);
      break;
    case 3:
      m_logger.setLogLevel(log4cplus::DEBUG_LOG_LEVEL);
      break;
    case 4:
      m_logger.setLogLevel(log4cplus::TRACE_LOG_LEVEL);
      break;
  }
}
