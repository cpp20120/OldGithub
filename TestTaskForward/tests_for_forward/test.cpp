#include "pch.h"


#include "../test_task_for_forward/parse_rules.cpp"
#include "../test_task_for_forward/engine_simulator_parser.cpp"

TEST(stod, space_in_string)
{
	std::string str = " 12412 ";
	EXPECT_EQ(12412, std::stod(str));
}

TEST(parse_rules, parse_vector)
{
	std::vector<double> V = { 123 };
	std::string str = "V = { 123 }";
	EXPECT_EQ(V, parse_rules::parse_vector(str));

	str = "V = {}";
	V = {};
	EXPECT_EQ(V, parse_rules::parse_vector(str));

	str = "V = {123, 456.1}";
	V = { 123, 456.1 };
	EXPECT_EQ(V, parse_rules::parse_vector(str));

	str = "V = {-123, 456.1}";
	V = { -123, 456.1 };
	EXPECT_EQ(V, parse_rules::parse_vector(str));
}

TEST(parse_rules, parse_double)
{
	std::string str = "C = 0.1";
	EXPECT_EQ(0.1, parse_rules::parse_double(str));

	str = "C = -0.1";
	EXPECT_EQ(-0.1, parse_rules::parse_double(str));
}

TEST(parser, parse)
{
	std::string str = "I = 10\n"
		"M = { 20, 75, 100, 105, 75, 0 }\n"
		"V = { 0, 75, 150, 200, 250, 300 }\n"
		"T = 90\n"
		"Hm = 0.01\n"
		"Hv = 0.0001\n"
		"C = 0.1";

	std::istringstream iss(str);

	engine_simulator_dto dto = engine_simulator_parser::parse(iss, 10);

	EXPECT_EQ(dto.inertia, 10);
	EXPECT_EQ(dto.critical_temperature, 90);
	EXPECT_DOUBLE_EQ(dto.heating_from_torque, 0.01);
	EXPECT_DOUBLE_EQ(dto.heating_from_crankshaft, 0.0001);
	EXPECT_DOUBLE_EQ(dto.cooling_coefficient, 0.1);

	std::vector<double> torque_points = { 20, 75, 100, 105, 75, 0 };
	std::vector<double> crankshaft_speed_points = { 0, 75, 150, 200, 250, 300};
	EXPECT_EQ(dto.torque_points, torque_points);
	EXPECT_EQ(dto.crankshaft_speed_points, crankshaft_speed_points);
}
