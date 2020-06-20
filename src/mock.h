/*
 * mock.h
 *
 *  Created on: Jun 19, 2020
 *      Author: tin
 */

#ifndef MOCK_H_
#define MOCK_H_

// some stub and mocking classes

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



#endif /* MOCK_H_ */
