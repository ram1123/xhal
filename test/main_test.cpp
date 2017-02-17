#include "units/getNode_t.cpp"
#include "units/parse_t.cpp"
#include "units/XHALInterface_t.cpp"

#include <iostream>
#include <chrono>


int main(int argc, char** argv)
{
  std::cout << "=================================" << std::endl;
  std::cout << "=================================" << std::endl;
  std::cout << "WELCOME TO XHAL TESTING FRAMEWORK" << std::endl;
  std::cout << "=================================" << std::endl;
  std::cout << "=================================" << std::endl;
  if (argc<2) 
  {
    std::cout << "Please provide address table filename" << std::endl;
    std::cout << "Usage: <path>/test <address_table>.xml" << std::endl;
    return 0;
  }
  int test_results[2];
  xhal::test::parse_t * t1 = new xhal::test::parse_t(argv[1]);
  std::cout<<std::endl;
  std::cout << "Start parsing test" << std::endl;
  auto begin = std::chrono::high_resolution_clock::now();
  test_results[0] = t1->launch();
  if (test_results[0]) 
  {
    std::cout << "parseXML test failed" << std::endl; // TODO call test summary function??
    return 1;
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "parsing test done in " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << " us" << std::endl;
  xhal::utils::XHALXMLParser * t_parser = t1->getParser();
  xhal::test::getNode_t * t2 = new xhal::test::getNode_t(t_parser);
  std::cout<<std::endl;
  std::cout << "Start getNode test" << std::endl;
  begin = std::chrono::high_resolution_clock::now();
  test_results[1] = t2->launch();
  if (test_results[1]) 
  {
    std::cout << "getNode test failed" << std::endl; // TODO call test summary function??
    return 1;
  }
  end = std::chrono::high_resolution_clock::now();
  std::cout << "getNode test done in " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << " us" << std::endl;

  if (t1) delete t1;
  if (t2) delete t2;

  xhal::test::XHALInterface_t * t3 = new xhal::test::XHALInterface_t("eagle34",argv[1]);
  std::cout << "Start XHALInterface test" << std::endl;
  std::cout << "=================================" << std::endl;
  std::cout << "Start init test" << std::endl;
  begin = std::chrono::high_resolution_clock::now();
  t3->init_t();
  end = std::chrono::high_resolution_clock::now();
  std::cout << "init test done in " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << " us" << std::endl;
  std::cout << "=================================" << std::endl;
  std::cout << "Start loadModule test" << std::endl;
  begin = std::chrono::high_resolution_clock::now();
  t3->loadModule_t();
  end = std::chrono::high_resolution_clock::now();
  std::cout << "loadModule test done in " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << " us" << std::endl;
  std::cout << "=================================" << std::endl;
  std::cout << "Start readRegByName test" << std::endl;
  begin = std::chrono::high_resolution_clock::now();
  t3->readRegByName_t();
  end = std::chrono::high_resolution_clock::now();
  std::cout << "readRegByName test done in " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << " us" << std::endl;
  std::cout << "=================================" << std::endl;
  std::cout << "Start writeReg test" << std::endl;
  begin = std::chrono::high_resolution_clock::now();
  t3->writeReg_only_t();
  end = std::chrono::high_resolution_clock::now();
  std::cout << "writeReg test done in " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << " us" << std::endl;
  std::cout << "=================================" << std::endl;
  std::cout << "Start writeReg completeness test" << std::endl;
  begin = std::chrono::high_resolution_clock::now();
  t3->writeReg_complete_test_t();
  end = std::chrono::high_resolution_clock::now();
  std::cout << "writeReg completeness test done in " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << " us" << std::endl;
  std::cout << "=================================" << std::endl;

  std::cout << "=================================" << std::endl;
  std::cout << "=================================" << std::endl;
  std::cout << "ALL TESTS PASSED SUCCESSFULLY" << std::endl;
  std::cout << "=================================" << std::endl;
  std::cout << "=================================" << std::endl;
  return 0;
}
