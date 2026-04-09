#include "Quadratic.h"
#include "Queue.h"
#include "Student.h"
#include "Teacher.h"
#include <vector>
#include <ctime>

int main() {
	srand(time(nullptr));

	std::vector<Quadratic> tasks = readequations("input.txt");

	std::vector<std::unique_ptr<Student>> students;
	students.push_back(std::make_unique<GoodStudent>("Inna"));
	students.push_back(std::make_unique<AverageStudent>("Jack"));
	students.push_back(std::make_unique<AverageStudent>("Matvey"));
	students.push_back(std::make_unique<BadStudent>("Max"));
	students.push_back(std::make_unique<BadStudent>("Anna"));
	students.push_back(std::make_unique<GoodStudent>("Zakhar"));

	Queue<Letter> mailbox;

	for (const auto& eq : tasks) {
		for (const auto& student : students) {
			Letter let(eq, student->solve(eq), student->getname());
			mailbox.push(let);
		}
	}

	Teacher teach;
	teach.checkall(mailbox);
	teach.printresults();

	return 0;
}
