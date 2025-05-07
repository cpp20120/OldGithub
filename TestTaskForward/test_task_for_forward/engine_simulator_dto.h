#pragma once

#include<vector>

struct engine_simulator_dto final
{
	std::vector<double> torque_points;
	std::vector<double> crankshaft_speed_points;

	double inertia			= 0;
	double acceleration		= 0;
	double temperature		= 0;	
	double torque			= 0;
	double crankshaft_speed = 0;

	double environment_temperature	= 0;
	double critical_temperature		= 0;

	double heating_from_torque		= 0;	
	double heating_from_crankshaft	= 0;	
	double cooling_coefficient		= 0;	

	double heating_speed = 0;
	double cooling_speed = 0;
};

