#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xhal/rpc/wiscrpcsvc.h"

#define DLLEXPORT extern "C"

#define STANDARD_CATCH \
	catch (wisc::RPCSvc::NotConnectedException &e) { \
		printf("Caught NotConnectedException: %s\n", e.message.c_str()); \
		return 1; \
	} \
	catch (wisc::RPCSvc::RPCErrorException &e) { \
		printf("Caught RPCErrorException: %s\n", e.message.c_str()); \
		return 1; \
	} \
	catch (wisc::RPCSvc::RPCException &e) { \
		printf("Caught exception: %s\n", e.message.c_str()); \
		return 1; \
	} \
	catch (wisc::RPCMsg::BadKeyException &e) { \
		printf("Caught exception: %s\n", e.key.c_str()); \
		return 0xdeaddead; \
	} 

#define ASSERT(x) do { \
		if (!(x)) { \
			printf("Assertion Failed on line %u: %s\n", __LINE__, #x); \
			return 1; \
		} \
	} while (0)

static wisc::RPCSvc rpc;
static wisc::RPCMsg req, rsp;

DLLEXPORT uint32_t init(char * hostname)
{
  try {
		rpc.connect(hostname);
	}
	catch (wisc::RPCSvc::ConnectionFailedException &e) {
		printf("Caught RPCErrorException: %s\n", e.message.c_str());
		return 1;
	}
	catch (wisc::RPCSvc::RPCException &e) {
		printf("Caught exception: %s\n", e.message.c_str());
		return 1;
	}

  try {
  		ASSERT(rpc.load_module("memory", "memory v1.0.1"));
  		ASSERT(rpc.load_module("extras", "extras v1.0.1"));
  		ASSERT(rpc.load_module("utils", "utils v1.0.1"));
  		ASSERT(rpc.load_module("optohybrid", "optohybrid v1.0.1"));
  	}
  	STANDARD_CATCH;

  return 0;
}

DLLEXPORT uint32_t update_atdb(char * xmlfilename)
{
	req = wisc::RPCMsg("utils.update_address_table");
	req.set_string("at_xml", xmlfilename);
	try {
		rsp = rpc.call_method(req);
	}
	STANDARD_CATCH;

	if (rsp.get_key_exists("error")) {
    return 1;
  }
	return 0;
}

DLLEXPORT uint32_t getRegInfoDB(char * regName)
{
  uint32_t address, mask;
  std::string permissions;
	req = wisc::RPCMsg("utils.readRegFromDB");
	req.set_string("reg_name", regName);
	try {
		rsp = rpc.call_method(req);
	}
	STANDARD_CATCH;

	if (rsp.get_key_exists("error")) {
    return 1;
  }
  printf("Register %s is found \n",regName);
  try {
    address = rsp.get_word("address");
    mask = rsp.get_word("mask");
    permissions = rsp.get_string("permissions");

    printf("Address: 0x%8x, permissions: %s, mask: 0x%8x \n", address, permissions.c_str(), mask);
  }
	STANDARD_CATCH;
	return 0;
}

DLLEXPORT uint32_t configureVT1(char * ohN, char * config, unsigned int vt1 = 0x64)
{
	req = wisc::RPCMsg("optohybrid.loadVT1");
	req.set_string("oh_number", ohN);
  req.set_word("vt1",vt1);
	if (config && config[0]!='\0') req.set_string("thresh_config_filename", config);
	try {
		rsp = rpc.call_method(req);
	}
	STANDARD_CATCH;

	if (rsp.get_key_exists("error")) {
    printf("Error: %s",rsp.get_string("error").c_str());
    return 1;
  }
	return 0;
}

DLLEXPORT uint32_t configureTRIMDAC(char * ohN, char * config)
{
	req = wisc::RPCMsg("optohybrid.loadTRIMDAC");
	req.set_string("oh_number", ohN);
	req.set_string("trim_config_filename", config);
	try {
		rsp = rpc.call_method(req);
	}
	STANDARD_CATCH;

	if (rsp.get_key_exists("error")) {
    printf("Error: %s",rsp.get_string("error").c_str());
    return 1;
  }
	return 0;
}

DLLEXPORT uint32_t configureVFATs(char * ohN, char * trim_config, char * thresh_config, unsigned int set_run = 1, unsigned int vt1 = 0x64)
{
	req = wisc::RPCMsg("optohybrid.configureVFATs");
	req.set_string("oh_number", ohN);
  req.set_word("vt1",vt1);
	req.set_string("trim_config_filename", trim_config);
  if (set_run) req.set_word("set_run", set_run);
	if (thresh_config && thresh_config[0]!='\0') req.set_string("thresh_config_filename", thresh_config);
	try {
		rsp = rpc.call_method(req);
	}
	STANDARD_CATCH;

	if (rsp.get_key_exists("error")) {
    printf("Error: %s",rsp.get_string("error").c_str());
    return 1;
  }
	return 0;
}

DLLEXPORT unsigned long getReg(unsigned int address)
{
	req = wisc::RPCMsg("memory.read");
	req.set_word("address", address);
	req.set_word("count", 1);
	try {
		rsp = rpc.call_method(req);
	}
	STANDARD_CATCH;

	uint32_t result;
  try{
	  if (rsp.get_key_exists("error")) {
      return 0xdeaddead;
    } else {
	    ASSERT(rsp.get_word_array_size("data") == 1);
      rsp.get_word_array("data", &result);
    }
  }
	STANDARD_CATCH;

	return result;
}

DLLEXPORT unsigned long getBlock(unsigned int address, uint32_t* result, ssize_t size)
{
 	req = wisc::RPCMsg("extras.blockread");
	req.set_word("address", address);
	req.set_word("count", size);
	try {
		rsp = rpc.call_method(req);
	}
	STANDARD_CATCH;

  try{
	  if (rsp.get_key_exists("error")) {
      return 1;
    } else {
	    ASSERT(rsp.get_word_array_size("data") == size);
      rsp.get_word_array("data", result);
    }
  }
	STANDARD_CATCH;
  return 0;
}

DLLEXPORT unsigned long getList(uint32_t* addresses, uint32_t* result, ssize_t size)
{
 	req = wisc::RPCMsg("extras.listread");
	req.set_word_array("addresses", addresses,size);
	req.set_word("count", size);
	try {
		rsp = rpc.call_method(req);
	}
	STANDARD_CATCH;

  try{
	  if (rsp.get_key_exists("error")) {
      return 1;
    } else {
	    ASSERT(rsp.get_word_array_size("data") == size);
      rsp.get_word_array("data", result);
    }
  }
	STANDARD_CATCH;
  return 0;
}
DLLEXPORT unsigned long putReg(unsigned int address, unsigned int value)
{
	req = wisc::RPCMsg("memory.write");
	req.set_word("address", address);
	req.set_word_array("data", &value,1);
	try {
		rsp = rpc.call_method(req);
	}
	STANDARD_CATCH;
  if (rsp.get_key_exists("error")) {
    return 0xdeaddead;
  } else return value;
}
