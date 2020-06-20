#ifndef MY_TEST_FRAMEWORK_H
#define MY_TEST_FRAMEWORK_H

#include <cstdio>
#include <functional>
#include <stdexcept>

using namespace std;

namespace MyTestFramework
{
    void assert_that(bool statement, const char* message);
	int run_test(void (*unit_test)(), const char* name);
}

#endif //MY_TEST_FRAMEWORK_H
