#pragma once
#include <map>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include "Quadratic.h"
#include "Student.h"
#include "Queue.h"

struct Letter {
	Quadratic equation;
	Answer answ;
	std::string studname;

	Letter(const Quadratic& eq, const Answer& ans, const std::string& name);
};

class Teacher {
private:
	std::map<std::string, int> results;

	std::map<std::string, Answer> solved_cache;

	bool check(const Quadratic& q, const Answer& ans);

public:
	void checkall(Queue<Letter>& mailbox);

	void printresults() const;
};
   
