#include <cstdio>
#include <functional>
#include <stdexcept>
#include "my_test_framework.h"
#include "AutoBrake.h"

using namespace std;

// **************************************
// our unit test
// **************************************

// Test initial_speed_is_zero
void initial_speed_is_zero() {
  AutoBrake auto_break{  [](const BrakeCommand&) {} };
  MyTestFramework::assert_that(auto_break.get_speed_mps() == 0L, "speed not equal 0");
}

int main() {
	MyTestFramework::run_test(initial_speed_is_zero, "initial speed is 0");
}
