#include <boost/python.hpp>
#include "xhal/XHALDevice.h"
#include "xhal/utils/PyTypes.h"
#include "xhal/rpc/daq_monitor.h"
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>

// https://stackoverflow.com/questions/7577410/boost-python-select-between-overloaded-methods
uint32_t (xhal::XHALDevice::*readReg_byname)(std::string regName) = &xhal::XHALDevice::readReg;
uint32_t (xhal::XHALDevice::*readReg_byaddress)(uint32_t address) = &xhal::XHALDevice::readReg;

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(getmonTRIGGERmain_overloads, getmonTRIGGERmain, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(getmonTRIGGEROHmain_overloads, getmonTRIGGEROHmain, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(getmonDAQOHmain_overloads, getmonDAQOHmain, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(getmonOHmain_overloads, getmonOHmain, 0, 1)

BOOST_PYTHON_MODULE(xhalpy){
  using namespace boost::python;

  class_<xhal::XHALDevice>("XHALDevice", init<const std::string&, const std::string&>())
    .def("connect",&xhal::XHALDevice::connect)
    .def("loadModule",&xhal::XHALDevice::loadModule)
    .def("setLogLevel",&xhal::XHALDevice::setLogLevel)
    .def("readReg",readReg_byname)
    .def("readReg",readReg_byaddress)
    .def("writeReg",&xhal::XHALDevice::writeReg);
  
  class_<PyListUint32>("PyListUint32")
    .def(vector_indexing_suite<PyListUint32>() );

  class_<PyDictVecUint32>("PyDictVecUint32")
    .def(map_indexing_suite<PyDictVecUint32>() );

  class_<xhal::rpc::DaqMonitor>("DaqMonitor", init<const std::string&>())
    .def("getmonTTCmain",&xhal::rpc::DaqMonitor::getmonTTCmain)
    .def("getmonTRIGGERmain",&xhal::rpc::DaqMonitor::getmonTRIGGERmain,getmonTRIGGERmain_overloads())
    .def("getmonTRIGGEROHmain",&xhal::rpc::DaqMonitor::getmonTRIGGEROHmain,getmonTRIGGEROHmain_overloads())
    .def("getmonDAQOHmain",&xhal::rpc::DaqMonitor::getmonDAQOHmain,getmonDAQOHmain_overloads())
    .def("getmonOHmain",&xhal::rpc::DaqMonitor::getmonOHmain,getmonOHmain_overloads())
    .def("getmonDAQmain",&xhal::rpc::DaqMonitor::getmonDAQmain);
}
