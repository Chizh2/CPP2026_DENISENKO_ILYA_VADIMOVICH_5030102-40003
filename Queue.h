#pragma once
#include <stdexcept>
template<typename T>

class Queue {
private:
	struct Node {

		T data;
		Node* next;

		Node(const T& value) : data(value), next(nullptr) {}
	};

	Node* first;
	Node* last;

public:
	Queue() : first(nullptr), last(nullptr) {}

	~Queue() {
		while (!empty()) {
			pop();
		}
	}

	void push(const T& value) {
		Node* node = new Node(value);

		if (last == nullptr) {
			first = last = node;
		}
		else {
			last->next = node;
			last = node;
		}
	}

	void pop() {
		if (first == nullptr) {
			return;
		}

		Node* temp = first;

		first = first->next;

		delete temp;

		if (first == nullptr) {
			last = nullptr;
		}
	}

	T& front() {
		if (first == nullptr) {
			throw std::runtime_error("Queue is empty");
		}
		return first->data;
	}

	const T& front() const{
		if (first == nullptr) {
			throw std::runtime_error("Queue is empty");
		}
		return first->data;
	}

	bool empty() const{
		return first == nullptr;
	}
};
