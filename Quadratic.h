#pragma once
#include <vector>
#include <cmath>
#include <fstream>
#include <string>

class quadratic {
private:
	double a, b, c;
public:
	quadratic(double a, double b, double c) : a(a), b(b), c(c) {}

	std::vector<double> solve() const {
		std::vector<double> roots;
		double D = b * b - 4 * a * c;
		if (D > 0) {
			roots.push_back((-b + sqrt(D)) / (2 * a));
			roots.push_back((-b - sqrt(D)) / (2 * a));
		}
		else if (D == 0) {
			roots.push_back(-b / (2 * a));
		}
		return roots;
	}
};

inline std::vector<quadratic> readequations(const std::string& filename) {
	std::vector<quadratic> equations;
	std::ifstream file(filename);

	double a, b, c;

	while (file >> a >> b >> c) {
		equations.push_back(quadratic(a, b, c));
	}

	return equations;
}