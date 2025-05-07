#pragma once

#include "engine_simulator_interface.h"

class test_engine final
{
public:
	test_engine() = delete;
	static size_t test(engine_simulator_interface& engine_simulator, size_t time_limit_seconds = -1);
};

