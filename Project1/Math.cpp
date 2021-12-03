#include "Math.h"

std::vector<double> Math::linspace(const double &min, const double &max, const uint32_t &precision)
{
	std::vector<double> sequence(precision);
	double dx = (max - min) / (precision - 1);
	for (int i=0;i<precision;i++)
	{
		sequence[i] = min + i * dx;
	}
	return sequence;
}