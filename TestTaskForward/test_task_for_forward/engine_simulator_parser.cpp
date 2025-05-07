#include "engine_simulator_parser.h"

#include <string>

#include "parse_rules.h"

engine_simulator_dto engine_simulator_parser::parse(std::istream& input, const double environment_temperature)
{

	engine_simulator_dto dto;
	dto.environment_temperature = environment_temperature;
	std::string str;
	int pos;

	for (int i = 0; i < 7; i++) {
		getline(input, str);

		switch (i) {
		case 0:
			dto.inertia = parse_rules::parse_double(str);
			break;
		case 1:
			dto.torque_points = parse_rules::parse_vector(str);
			break;
		case 2:
			dto.crankshaft_speed_points = parse_rules::parse_vector(str);
			break;
		case 3:
			dto.critical_temperature = parse_rules::parse_double(str);
			break;
		case 4:
			dto.heating_from_torque = parse_rules::parse_double(str);
			break;
		case 5:
			dto.heating_from_crankshaft = parse_rules::parse_double(str);
			break;
		case 6:
			dto.cooling_coefficient = parse_rules::parse_double(str);
			break;
		}
	}
	if (dto.torque_points.size() != dto.crankshaft_speed_points.size())
	{
		throw std::runtime_error("Invalid input format: vectors have different sizes");
	}
	if (dto.inertia < 0 || dto.heating_from_torque < 0 || dto.heating_from_crankshaft < 0 || dto.cooling_coefficient < 0)
	{
		throw std::runtime_error("Invalid input format: some values are negative");
	}
	for (size_t i = 0; i < dto.torque_points.size(); i++)
	{
		if (dto.torque_points[i] < 0 || dto.crankshaft_speed_points[i] < 0)
		{
			throw std::runtime_error("Invalid input format: some values in vector are negative");
		}
	}
	return dto;
}
