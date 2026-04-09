#include "Teacher.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Quadratic.h"
#include "Student.h"
#include "Queue.h"

Letter::Letter(const Quadratic& eq, const Answer& ans,  const std::string& name) : equation(eq), answ(ans), studname(name) {}

bool Teacher::check(const Quadratic& q, const Answer& ans) {
	std::string key = std::to_string(q.getA()) + "," + std::to_string(q.getB()) + "," + std::to_string(q.getC());

	std::vector<double> correct;

	if (solved_cache.count(key)) {
		correct = solved_cache[key];
	}
	else {
		correct = q.solve();
		solved_cache[key] = correct; 
	}

	if (correct.size() != ans.size()) {
		return false;
	}

	std::vector<double> correct_sorted = correct;
	std::vector<double> ans_sorted = ans;

	std::sort(correct_sorted.begin(), correct_sorted.end());
	std::sort(ans_sorted.begin(), ans_sorted.end());
	for (size_t i = 0; i < correct.size(); i++) {
		if (fabs(correct_sorted[i] - ans_sorted[i]) > 1e-6) {
			return false;
		}
	}

	return true;
}

void Teacher::checkall(Queue<Letter>& mailbox) {
	while (!mailbox.empty()) {

		Letter l = mailbox.front();

		mailbox.pop();

		results.try_emplace(l.studname, 0);

		if (check(l.equation, l.answ)) {
			results[l.studname]++;
		}
	}
}

void Teacher::printresults() const {
	std::cout << "Results:\n";

	for (auto& r : results) {
		std::cout << r.first << " : " << r.second << std::endl;
	}
}
