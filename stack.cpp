#include <iostream>
#include <algorithm>
#include <memory>
#include <stdexcept>

using namespace std;

class Stack {
	int top_;
	int capacity_;
	int* data_;

	static const int CHUNK_SIZE = 15;

	void resize() {
		int* old_data = data_;
		capacity_ += CHUNK_SIZE;
		data_ = new int[capacity_];
		copy(old_data, old_data + top_, data_);
		delete [] old_data;
	}

public:
	Stack() : top_(0), capacity_(CHUNK_SIZE), data_(new int[capacity_]) {}
	
	~Stack() {
		delete [] data_;
	}
	
	Stack(const Stack& other) : top_(other.top_), capacity_(other.capacity_), data_(new int[capacity_]) {
		copy(other.data_, other.data_ + other.top_, data_);
	}
	
	Stack& operator=(const Stack& other) {
		if (this != &other) {
			delete [] data_;
			top_ = other.top_;
			capacity_ = other.capacity_;
			data_ = new int[capacity_];
			copy(other.data_, other.data_ + top_, data_);
		}
		return *this;
	}
	
	Stack(Stack&& other) noexcept : top_(move(other.top_)), capacity_(move(other.capacity_)), data_(new int[capacity_]) {
		move(other.data_, other.data_ + top_, data_);
	}
	
	Stack& operator=(Stack&& other) {
		if (this != addressof(other)) {
			delete [] data_;
			top_ = move(other.top_);
			capacity_ = move(other.capacity_);
			data_ = new int[capacity_];
			move(other.data_, other.data_ + top_, data_);
		}
		return *this;
	}
	
	bool empty() const {
		return top_ == 0;
	}
	
	void push(const int& val) {
	 	if (top_ == capacity_) {
			resize();
		}
		data_[top_++] = val;
	}

	int pop() {
		if (empty()) {
			throw runtime_error("empty stack");
		}
		return data_[--top_];
	}
};

int main() {
	Stack st;
	cout << boolalpha << st.empty() << endl;
	for(int i=0; i<10; ++i) {
		st.push(i*42);
	}
	Stack st1=st;
	while(!st1.empty()) {
		cout << "st1: " << st1.pop() << endl;
	}
	Stack st2;
	st2 = st;
	while(!st2.empty()) {
		cout << "st2: " << st2.pop() << endl;
	}
	st = st;
	while(!st.empty()) {
		cout << st.pop() << endl;
	}
	return 0;
}
