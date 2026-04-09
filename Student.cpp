#include "Student.h"
#include <cstdlib>

Student::Student(std::string name) : name(name) {}

std::string Student::getname() const {
	return name;
}

Student::~Student() {}

GoodStudent::GoodStudent(std::string name) : Student(name) {}
Answer GoodStudent::solve(const Quadratic& q) {
	Answer ans;

	ans = q.solve();

	return ans;
}

AverageStudent::AverageStudent(std::string name) : Student(name) {}
Answer AverageStudent::solve(const Quadratic& q) {
	Answer ans;

	if (rand() % 2 == 0) {
		ans = q.solve();
	}
	else {
		ans = { 0 };
	}

	return ans;
}

BadStudent::BadStudent(std::string name) : Student(name) {}

Answer BadStudent::solve(const Quadratic& q) {
	Answer ans;

	ans = { 0 };

	return ans;
}
    
