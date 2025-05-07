#pragma once

#include <vector>
#include <string>

class parse_rules final
{
public:
	parse_rules() = delete;
	static double parse_double(std::string& str);
	static std::vector<double> parse_vector(const std::string& str);
};

