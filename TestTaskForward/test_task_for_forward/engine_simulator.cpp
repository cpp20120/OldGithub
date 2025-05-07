#include "engine_simulator.h"

engine_simulator::engine_simulator(const engine_simulator_dto& dto): converter_(torque_from_speed_converter(
																	 dto.torque_points, dto.crankshaft_speed_points)),
                                                                     inertia_(dto.inertia),
                                                                     environment_temperature_(dto.environment_temperature),
                                                                     critical_temperature_(dto.critical_temperature),
                                                                     heating_from_torque_(dto.heating_from_torque),
                                                                     heating_from_crankshaft_(dto.heating_from_crankshaft),
                                                                     cooling_coefficient_(dto.cooling_coefficient)
{
	acceleration_ = 0;
	temperature_ = environment_temperature_;
	torque_ = 0;
	crankshaft_speed_ = 0;
	heating_speed_ = 0;
	cooling_speed_ = 0;
}

void engine_simulator::update_state()
{
	torque_ = converter_.convert(crankshaft_speed_);
	acceleration_ = torque_ / inertia_;
	heating_speed_ = torque_ * heating_from_torque_ + crankshaft_speed_ * crankshaft_speed_ * heating_from_crankshaft_;
	cooling_speed_ = cooling_coefficient_ * (environment_temperature_ - temperature_);
	crankshaft_speed_ += acceleration_;
	temperature_ += heating_speed_ + cooling_speed_;

}

double engine_simulator::get_crankshaft_speed()
{
	return crankshaft_speed_;
}

double engine_simulator::get_temperature()
{
	return temperature_;
}

bool engine_simulator::is_critical_temperature()
{
	return temperature_ >= critical_temperature_;
}
