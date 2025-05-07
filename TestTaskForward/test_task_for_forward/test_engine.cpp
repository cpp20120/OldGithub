#include "test_engine.h"

size_t test_engine::test(engine_simulator_interface& engine_simulator, const size_t time_limit_seconds)
{
	size_t seconds_passed = 0;
	while (!engine_simulator.is_critical_temperature() && seconds_passed < time_limit_seconds)
	{
		engine_simulator.update_state();
		++seconds_passed;
	}
	return seconds_passed;
}
