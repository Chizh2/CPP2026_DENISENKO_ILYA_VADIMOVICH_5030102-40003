#pragma once

template<typename T>

class queue {
private:
	struct Node {
		T data;
		Node* next;
		Node(const T& value) : data(value), next(nullptr) {}
	};

	Node* first;
	Node* last;

public:
	queue() :first(nullptr), last(nullptr) {}

	~queue() {
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
		return first->data;
	}

	bool empty() {
		return first == nullptr;
	}
};
