#ifndef AUTOBRAKE_H
#define AUTOBRAKE_H

#include <cstdio>
#include <functional>
#include <stdexcept>
#include "mock.h"


template <typename T>
class AutoBrake
{
public:
	AutoBrake(const T& pub):publish( pub ) {}

	void observe(const SpeedUpdate& su){
		speed_mps = su.velocity_mps;
	};
	void observe(const CarDetected& cd)
	{
		// calculate time to collision, assume car is alway in front
		// publish brake when time to collision lower than threshold
		const auto relative_velocity_mps = speed_mps - cd.velocity_mps;
		const auto time_to_collision_s = cd.distance_m / relative_velocity_mps;

		if( time_to_collision_s > 0 &&
				time_to_collision_s <= collision_threshold_s) {
			publish(BrakeCommand{time_to_collision_s});
		}
	};

	void set_collision_threshold_s(double x)
	{
		if(x<1){
			throw std::runtime_error("collision threshold < 1");
		}
		collision_threshold_s = 5;
	};

	double get_collision_threshold_s(void) const
	{
		return collision_threshold_s;
	}

	double get_speed_mps(void) const
	{
		return speed_mps;
	}

private:
	double collision_threshold_s{5};
	double speed_mps{0};
	const T& publish{};
};

#endif // AUTOBRAKE_H

