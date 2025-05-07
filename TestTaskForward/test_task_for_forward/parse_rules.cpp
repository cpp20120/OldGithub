#include "parse_rules.h"
#include <sstream>

double parse_rules::parse_double(std::string& str)
{
	const int pos = str.find('=');
	str[pos] = ' ';
	str = str.substr(pos);
	return std::stod(str);
}

std::vector<double> parse_rules::parse_vector(const std::string& str)
{
	std::string cleaned_str(str.size(), ' ');

	for (size_t i = 0; i < str.size(); ++i)
	{
		if (!(std::isdigit(str[i]) || str[i] == ' ' || str[i] == '.' || str[i] == '-'))
		{
			continue;
		}
		cleaned_str[i] = str[i];
	}

	std::istringstream iss(cleaned_str);

	std::vector<double> elements;

	double element;

	while(iss >> element) 
	{
		elements.push_back(element);
	}

	return elements;
}
