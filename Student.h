#pragma once
#include <vector>
#include <string>
#include "Quadratic.h"

using Answer = std::vector<double>;

class Student {
protected:
	std::string name;
public:
	Student(const std::string name);

	virtual Answer solve(const Quadratic& q) = 0;

	std::string getname() const;

	virtual ~Student();
};

class GoodStudent : public Student {
public:
	GoodStudent(const std::string name);

	Answer solve(const Quadratic& q) override;
};

class AverageStudent : public Student {
public:
	AverageStudent(const std::string name);

	Answer solve(const Quadratic& q) override;
};

class BadStudent : public Student {
public:
	BadStudent(const std::string name);

	Answer solve(const Quadratic& q) override;
};
    
