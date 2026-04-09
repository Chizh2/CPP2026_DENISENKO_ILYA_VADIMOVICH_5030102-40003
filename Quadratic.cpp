#include "Quadratic.h"
#include <cmath>
#include <fstream>
#include <iostream>

Quadratic::Quadratic(double a, double b, double c) : a(a), b(b), c(c) {}

std::vector<double> Quadratic::solve() const {
	std::vector<double> roots;

	double D = b * b - 4 * a * c;
	const double EPS = 1e-6;

	if (fabs(a) < EPS) {           
		if (fabs(b) < EPS) {      

		}
		else {
			roots.push_back(-c / b); 
		}
	}
	else {                       
		double D = b * b - 4 * a * c;
		if (D > 0) {
			roots.push_back((-b + sqrt(D)) / (2 * a));
			roots.push_back((-b - sqrt(D)) / (2 * a));
		}
		else if (fabs(D) < EPS) {
			roots.push_back(-b / (2 * a));
		}
	}
	return roots;
}

double Quadratic::getA() const {
	return a;
}

double Quadratic::getB() const {
	return b;
}

double Quadratic::getC() const {
	return c;
}

std::vector<Quadratic> readequations(const std::string& filename) {
	std::vector<Quadratic> equations;

	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cout << "Error: could not open file " << filename << std::endl;
		return equations; 
	}
	double a, b, c;

	while (file >> a >> b >> c) {
		equations.push_back(Quadratic(a, b, c));
	}

	return equations;
}
