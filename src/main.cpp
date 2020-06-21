#include <cstdio>
#include <functional>
#include <stdexcept>
#include "my_test_framework.h"
#include "AutoBrake.h"

// **************************************
// our unit test
// **************************************

using namespace MyTestFramework;

void initial_speed_is_zero() {
  AutoBrake auto_brake{  [](const BrakeCommand&) {} };
  mytest_assert_that(auto_brake.get_speed_mps() == 0, "speed not equal 0");
}

void inital_sensitivity_is_five() {
	AutoBrake auto_brake{  [](const BrakeCommand&) {} };
	mytest_assert_that(auto_brake.get_collision_threshold_s() == 5,
			"sensitivity is not five");
}

void inital_always_greater_than_one() {
	AutoBrake auto_brake{  [](const BrakeCommand&) {} };
	try {
		auto_brake.set_collision_threshold_s(0.5);
	} catch ( const std::exception&) {
		return;
	}
	mytest_assert_that(false, "no exception thrown");
}

void speed_stored_persistent() {
	AutoBrake auto_brake{  [](const BrakeCommand&) {} };
	auto_brake.observe(SpeedUpdate {100} );
	mytest_assert_that(auto_brake.get_speed_mps() == 100, "speed not stored persistent 100");

	auto_brake.observe(SpeedUpdate {50} );
	mytest_assert_that(auto_brake.get_speed_mps() == 50, "speed not stored persistent 50");

	auto_brake.observe(SpeedUpdate {0} );
	mytest_assert_that(auto_brake.get_speed_mps() == 0, "speed not stored persistent 0");
}

// FIXME declaring "no_of_brake_command" locally leads in program termination
// life cycle/ storage duration issue? compiler optimization on anonymous function?
int no_of_brake_command{0};

void publish_collision_within_threshold() {
	no_of_brake_command = 0;
	AutoBrake auto_brake{
		[&no_of_brake_command](const BrakeCommand&) {
			no_of_brake_command++;
		}
	};
	auto_brake.set_collision_threshold_s(10);
	auto_brake.observe(SpeedUpdate{100});
	auto_brake.observe(CarDetected{100, 0});
	mytest_assert_that(no_of_brake_command == 1, "alert brake command");
}

void not_publish_collision_outside_threshold() {
	no_of_brake_command = 0;
	AutoBrake auto_brake{
		[&no_of_brake_command](const BrakeCommand&) {
			no_of_brake_command++;
		}
	};
	auto_brake.set_collision_threshold_s(2);
	auto_brake.observe(SpeedUpdate{100});
	auto_brake.observe(CarDetected{1000, 50});
	mytest_assert_that(no_of_brake_command == 0, "dont alert brake command");
}

int main() {
	// NOTE, make sure test fails first. I usually forget to add the test here
	// run test
	mytest_run_test(initial_speed_is_zero, "initial speed is 0");
	mytest_run_test(inital_sensitivity_is_five, "sensitivity is 5");
	mytest_run_test(inital_always_greater_than_one, "sensitivity always > 1");
	mytest_run_test(speed_stored_persistent, "store speed persistent");
	mytest_run_test(publish_collision_within_threshold, "publish brake command");
	mytest_run_test(not_publish_collision_outside_threshold, "not publish brake command");
	std::cout << "=== END OF TEST ===" << std::endl;
}
