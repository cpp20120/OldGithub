#pragma once

#include <istream>
#include "engine_simulator_dto.h"

class engine_simulator_parser final
{
public:
	engine_simulator_parser() = delete;
	static engine_simulator_dto parse(std::istream& input, double environment_temperature);
};

