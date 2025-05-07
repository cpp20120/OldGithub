#include "torque_from_speed_converter.h"


torque_from_speed_converter::torque_from_speed_converter(const std::vector<double>& torque_points,
                                                         const std::vector<double>& crankshaft_speed_points): torque_points_(torque_points),
																											  crankshaft_speed_points_(crankshaft_speed_points)
{
}

double torque_from_speed_converter::convert(const double speed) const noexcept
{
	double result = -1;
	for(size_t i = 1; i < crankshaft_speed_points_.size(); ++i)
	{
		if (speed < crankshaft_speed_points_[i])
		{
			const double k = (torque_points_[i] - torque_points_[i - 1]) / (crankshaft_speed_points_[i] - crankshaft_speed_points_[i - 1]);
			const double b = torque_points_[i] - k * crankshaft_speed_points_[i];
			result = k * speed + b;
			break;
		}
	}
	return result;
}
