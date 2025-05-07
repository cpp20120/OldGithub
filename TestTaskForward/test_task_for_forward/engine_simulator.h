#pragma once

#include "engine_simulator_interface.h"
#include "torque_from_speed_converter.h"
#include "engine_simulator_dto.h"

class engine_simulator final : public engine_simulator_interface
{
private:

	torque_from_speed_converter converter_;

	double inertia_;
	double acceleration_;
	double temperature_;
	double torque_;
	double crankshaft_speed_;

	const double environment_temperature_;
	const double critical_temperature_;

	const double heating_from_torque_;	
	const double heating_from_crankshaft_;
	const double cooling_coefficient_;	

	double heating_speed_;
	double cooling_speed_;

public:
	engine_simulator(const engine_simulator_dto& dto);

	void update_state() override;
	double get_crankshaft_speed() override;
	double get_temperature() override;

	[[nodiscard]] bool is_critical_temperature() override;
};

