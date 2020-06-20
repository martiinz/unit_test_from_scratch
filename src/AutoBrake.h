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
	//AutoBrake(const T& pub);
	AutoBrake(const T& pub):publish( pub ) {}

	void observe(const SpeedUpdate& su){};
	void observe(const CarDetected& cd){};

	void set_collision_threshold_s(double x){};

	double get_collision_threshold_s(void) const
	{
		return collision_threshold_s;
	}

	double get_speed_mps(void) const
	{
		return speed_mps;
	}

private:
	double collision_threshold_s{};
	double speed_mps{1}; // make inital_speed test fail
	const T& publish{};
};

#endif // AUTOBRAKE_H

