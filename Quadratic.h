#pragma once
#include <vector>
#include <string>

class Quadratic {
private:
	double a, b, c;

public:
	Quadratic(double a, double b, double c);

	std::vector<double> solve() const;
	double getA() const;
	double getB() const;
	double getC() const;
};

std::vector<Quadratic> readequations(const std::string& filename);
    
