#include <cstdio>
#include <functional>
#include <stdexcept>

using namespace std;

// the speed service mock,
// where we subscibe for speed changes
struct SpeedUpdate {
  double velocity_mps{};
};

// the car detector,
// where we subscribe for spotted cars
struct CarDetected {
  double distance_m{};
  double velocity_mps{};
};

// the brake service
// where we will publish coming brakes
struct BrakeCommand {
  double time_to_collision_s{};
};

// AutoBrake, our brake implementation
// a skeleton so far
template <typename T>
struct AutoBrake {
  AutoBrake(const T& publish) : publish{ publish } {}
  void observe(const SpeedUpdate& su) {};
  void observe(const CarDetected& cd) {};

  void set_collision_threshold_s(double x) {
    collision_threshold_s = x;
  }

  double get_collision_threshold_s() const {
    return collision_threshold_s;
  }

  double get_speed_mps() const {
    return speed_mps;
  }

  private:
  double collision_threshold_s{};
  double speed_mps{1}; // make inital_speed test fail
  const T& publish{};
};


// **************************************
// our test framework implementation
// **************************************
void assert_that(bool statement, const char* message) {
  if(!statement)
    throw runtime_error(message);
}

int run_test(void (*unit_test)(), const char* name) {
  try {
    unit_test();
    printf("[+] Test %s successful.\n", name);
    return 0;
  } catch(const exception& e) {
    printf("[-] Test failure in %s. %s.\n", name, e.what());
  }
  return -1;
}


// **************************************
// our unit test
// **************************************

// Test initial_speed_is_zero
void initial_speed_is_zero() {
  AutoBrake auto_break{  [](const BrakeCommand&) {} };
  assert_that(auto_break.get_speed_mps() == 0L, "speed not equal 0");
}

int main() {
  run_test(initial_speed_is_zero, "initial speed is 0");
}
