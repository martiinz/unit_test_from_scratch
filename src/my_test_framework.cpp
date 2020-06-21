// **************************************
// my test framework implementation
// **************************************

#include "my_test_framework.h"

namespace MyTestFramework
{
	void mytest_assert_that(bool statement, const char* message) {
	  if(!statement)
		throw runtime_error(message);
	}

	int mytest_run_test(void (*unit_test)(), const char* name) {
	  try {
		unit_test();
		std::cout << "[+] Test " << name << " successful." << std::endl;
		return 0;
	  } catch(const exception& e) {
		std::cout << "[-] Test failure in " << name << ", " << e.what() << std::endl;
	  }
	  return -1;
	}
}
