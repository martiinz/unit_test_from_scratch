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
		printf("[+] Test %s successful.\n", name);
		return 0;
	  } catch(const exception& e) {
		printf("[-] Test failure in %s. %s.\n", name, e.what());
	  }
	  return -1;
	}
}
