/*
 * my_test_framework.h
 * our test framework from scratch implementation
 *
 *  Created on: Jun 19, 2020
 *      Author: tin
 */

#ifndef MY_TEST_FRAMEWORK_H
#define MY_TEST_FRAMEWORK_H

#include <cstdio>
#include <iostream>
#include <functional>
#include <stdexcept>

using namespace std;

namespace MyTestFramework
{
    void mytest_assert_that(bool statement, const char* message);
	int mytest_run_test(void (*unit_test)(), const char* name);
}

#endif //MY_TEST_FRAMEWORK_H
