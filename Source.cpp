#include "Quadratic.h"
#include "Queue.h"
#include "Student.h"
#include "Teacher.h"
#include <vector>

int main() {
	srand(time(nullptr));

	std::vector<quadratic> tasks = readequations("input.txt");
	std::vector<student*> students;
	students.push_back(new goodstudent("Inna"));
	students.push_back(new averagestudent("Jack"));
	students.push_back(new averagestudent("Matvey"));
	students.push_back(new badstudent("Max"));
	students.push_back(new badstudent("Anna"));
	students.push_back(new goodstudent("Zakhar"));

	queue<letter> mailbox;
	for (const auto& eq : tasks) {
		for (auto student : students) {
			letter let(eq, student->solve(eq), student->getname());
			mailbox.push(let);
		}
	}
	teacher teach;
	teach.checkall(mailbox);
	teach.printresults();

	for (auto s : students) {
		delete s;
	}
	return 0;
}