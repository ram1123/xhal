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

DLLEXPORT uint32_t init()
{
  try {
		rpc.connect("eagle45");
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
  	}
  	STANDARD_CATCH;

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
	  ASSERT(rsp.get_word_array_size("data") == 1);
	  rsp.get_word_array("data", &result);
  }
	STANDARD_CATCH;

	return result;
}

DLLEXPORT unsigned long putReg(unsigned int address, unsigned int value)
{
	req = wisc::RPCMsg("memory.write");
	req.set_word("address", address);
	req.set_word("count", 1);
	req.set_word("data", value);
	try {
		rsp = rpc.call_method(req);
	}
	STANDARD_CATCH;

	uint32_t result;
	ASSERT(rsp.get_word_array_size("data") == 1);
	rsp.get_word_array("data", &result);

	return result;
}
