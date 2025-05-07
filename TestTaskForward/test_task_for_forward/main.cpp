#include <iostream>
#include <fstream>
#include "engine_simulator_dto.h"
#include "engine_simulator_parser.h"
#include "engine_simulator.h"
#include "test_engine.h"

int main() {
	std::string path = "config.txt";

	std::ifstream input(path);
	if (!input)
	{
		std::cout << "Can't open file " << path << std::endl;
		return -2;
	}
	double environment_temperature = 0;
	std::cout << "Enter environment temperature" << std::endl;
	while(!(std::cin >> environment_temperature))
	{
		std::cout << "Incorrect temperature value. Try again" << std::endl;
	}
	engine_simulator_dto dto;
	try
	{
		dto = engine_simulator_parser::parse(input, environment_temperature);
	}
	catch(std::runtime_error& err)
	{
		std::cout << err.what() << std::endl;
		return -3;
	}
	engine_simulator engine(dto);
	const size_t limit_seconds = 1000000;
	size_t seconds = test_engine::test(engine, limit_seconds);
	if(seconds == limit_seconds)
	{
		std::cout << "Limit of " << limit_seconds << "sec is passed without overheating. All is ok" << std::endl;
	}
	else
	{
		std::cout << seconds << " seconds passed before overheat" << std::endl;
	}
	

	return 0;
}
