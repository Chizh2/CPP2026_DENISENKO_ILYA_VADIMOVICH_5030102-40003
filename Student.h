#pragma once
#include <vector>
#include <string>
#include "Quadratic.h"

struct answer {
	std::vector<double> roots;
};

class student {
protected:
	std::string name;
public:
	student(std::string name) : name(name) {}

	virtual answer solve(const quadratic& q) = 0;

	std::string getname() const {
		return name;
	}
	virtual ~student() {}
};

class goodstudent : public student {
public:
	goodstudent(std::string name) :student(name) {}

	answer solve(const quadratic& q) override {
		answer ans;
		ans.roots = q.solve();

		return ans;
	}
};

class averagestudent : public student {
public:
	averagestudent(std::string name) :student(name) {}

	answer solve(const quadratic& q) override {
		answer ans;
		if (rand() % 2 == 0) {
			ans.roots = q.solve();
		}
		else {
			ans.roots = { 0 };
		}

		return ans;
	}
};
class badstudent : public student {
public:
	badstudent(std::string name) :student(name) {}

	answer solve(const quadratic& q) override {
		answer ans;
		ans.roots = { 0 };
		return ans;
	}
};
