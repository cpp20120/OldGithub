#pragma once
class engine_simulator_interface
{
public:
	virtual double get_crankshaft_speed() = 0;
	virtual double get_temperature() = 0;
	virtual void update_state() = 0;
	virtual bool is_critical_temperature() = 0;

	virtual ~engine_simulator_interface() = default;
};

