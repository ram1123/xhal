#include <boost/python.hpp>
#include "xhal/XHALDevice.h"

using namespace boost::python;

// https://stackoverflow.com/questions/7577410/boost-python-select-between-overloaded-methods
uint32_t (xhal::XHALDevice::*readReg_byname)(std::string regName) = &xhal::XHALDevice::readReg;
uint32_t (xhal::XHALDevice::*readReg_byaddress)(uint32_t address) = &xhal::XHALDevice::readReg;

BOOST_PYTHON_MODULE(xhalpy){
  class_<xhal::XHALDevice>("XHALDevice", init<const std::string&, const std::string&>())
    .def("connect",&xhal::XHALDevice::connect)
    .def("loadModule",&xhal::XHALDevice::loadModule)
    .def("setLogLevel",&xhal::XHALDevice::setLogLevel)
    .def("readReg",readReg_byname)
    .def("readReg",readReg_byaddress)
    .def("writeReg",&xhal::XHALDevice::writeReg);
}
