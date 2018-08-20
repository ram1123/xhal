#include <boost/python.hpp>
#include "xhal/XHALInterface.h"

using namespace boost::python;

// https://stackoverflow.com/questions/7577410/boost-python-select-between-overloaded-methods
uint32_t (xhal::XHALInterface::*readReg_byname)(std::string regName) = &xhal::XHALInterface::readReg;
uint32_t (xhal::XHALInterface::*readReg_byaddress)(uint32_t address) = &xhal::XHALInterface::readReg;

BOOST_PYTHON_MODULE(xhalpy){
  class_<xhal::XHALInterface>("XHALInterface", init<const std::string&, const std::string&>())
    .def("init",&xhal::XHALInterface::init)
    .def("loadModule",&xhal::XHALInterface::loadModule)
    .def("setLogLevel",&xhal::XHALInterface::setLogLevel)
    .def("readReg",readReg_byname)
    .def("readReg",readReg_byaddress)
    .def("writeReg",&xhal::XHALInterface::writeReg);
}
