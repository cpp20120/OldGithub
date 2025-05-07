#pragma once

#include <vector>

class torque_from_speed_converter final
{
private:
	std::vector<double> torque_points_;
	std::vector<double> crankshaft_speed_points_;
public:
	torque_from_speed_converter(const std::vector<double> &torque_points, const std::vector<double> &crankshaft_speed_points);

	[[nodiscard]] double convert(double speed) const noexcept;
};

