#pragma once
#include <iostream>
#include <map>
#include <cmath>
#include "Queue.h"

class letter {
private:
	quadratic equation;
	answer answ;
	std::string studname;
public:
	letter(const quadratic& eq, const answer& ans, const std::string& name) : equation(eq), answ(ans), studname(name) {}
	friend class teacher;
};

class teacher {
private:
	std::map<std::string, int> results;

	bool check(const quadratic& q, const answer& ans) {
		std::vector<double> correct = q.solve();

		if (correct.size() != ans.roots.size()) {
			return false;
		}

		for (size_t i = 0; i < correct.size(); i++) {
			if (fabs(correct[i] - ans.roots[i]) > 1e-6) {
				return false;
			}
		}
		return true;
	}
public:
	void checkall(queue<letter>& mailbox) {
		while (!mailbox.empty()) {
			letter l = mailbox.front();
			mailbox.pop();

			results[l.studname];

			if (check(l.equation, l.answ)) {
				results[l.studname]++;
			}
		}
	}

	void printresults() const {
		std::cout << "Results:\n";
		for (auto& r : results) {
			std::cout << r.first << " : " << r.second << std::endl;
		}
	}
};
