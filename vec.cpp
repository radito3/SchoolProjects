#include <iostream>
#include <cstdlib>

using namespace std;

class VectorError {};

template<class T>
class Vector {
	static const int MAX_SIZE = 30;
	int capacity_;
	int size_;
	T* buffer_;
	void resize() {
		T* old_ = buffer_;
		capacity_ += MAX_SIZE;
		buffer_ = new T[capacity_];
		for (int i = 0; i < size_; ++i) {
			buffer_[i] = old_[i];
		}
	}
public:
	Vector(int capacity = 10)
		: capacity_(capacity),
		size_(0),
		buffer_(new T[capacity]) {}
	~Vector() {
		delete [] buffer_;
	}
	Vector(const Vector<T>& other)
		: size_(other.size_),
		capacity_(other.capacity_),
		buffer_(new T[capacity_]) {
		for (int i = 0; i < size_; i++) {
			buffer_[i] = other.buffer_[i];
		}
	}
	Vector<T>& operator=(const Vector<T>& other) {
		capacity_ = other.capacity_;
		size_ = other.size_;
		buffer_ = new T[capacity_];
		for (int i = 0; i < size_; i++) {
			buffer_[i] = other.buffer_[i];
		}
		return *this;
	}
	bool empty() const {
		return size_ == 0;
	}
	int size() const {
		return size_;
	}
	T& operator[](int n) {
		if (n > size_ || n > capacity_) {
			throw VectorError();
		}
		return buffer_[n];
	}
	const T& operator[](int n) const {
		if (n > size_ || n > capacity_) {
			throw VectorError();
		}
		return buffer_[n];
	}
	void clear() {
		if (!empty()) {
			delete [] buffer_;
			size_ = 0;
		}
	}
	int capacity() const {
		if (capacity_ < size_) {
			throw VectorError();
		}
		return capacity_;
	}
	T& front() {
		return buffer_[0];
	}
	const T& front() const {
		return buffer_[0];
	}
	T& back() {
		return buffer_[size_ - 1];
	}
	const T& back() const {
		return buffer_[size_ - 1];
	}
	void push_back(const T& val) {
		if (size_ > capacity_) {
			resize();
		}
		buffer_[size_++] = val;
	}
	void pop_back() {
		if (!empty()) {
			buffer_[size_ - 1] = NULL;
			size_--;
		} else throw VectorError();
	}
	class iterator {
		T* index_;
	public:
		iterator(T* index) : index_(index) {}
		T& operator*() {
			return *index_;
		}
		iterator operator++() {
			return iterator(++index_);
		}
		iterator operator++(int) {
			return iterator(index_++);
		}
		iterator operator--(int) {
			return iterator(index_--);
		}
		iterator operator--() {
			return iterator(--index_);
		}
		iterator operator+(int x) {
			for (int i = 0; i < x; i++) {
				index_++;
			}
			return *this;
		}
		bool operator!=(const iterator& other) const {
			return index_ != other.index_;
		}
		bool operator==(const iterator& other) const {
			return index_ == other.index_;
		}
	};
	iterator begin() {
		return &buffer_[0];
	}
	iterator end() {
		return &buffer_[size()];
	}
	int where(iterator pos) const {
		if (!empty()) {
			int i = 0;
			for (; buffer_[i] != *pos; i++);
			return ++i;
		} else throw VectorError();
	}
	iterator insert(iterator pos, const T& x) {
		size_++;
		if (size_ > capacity_) {
			resize();
		}
		int i = 0;
		for (; buffer_[i] != *pos; i++);
		int j = i + 1, at = i;
		for (; j < size() - 2; j++) {
			buffer_[j + 1] = buffer_[j];
		}
		buffer_[at] = x;
		return iterator(--pos);
	}
	iterator erase(iterator pos) {
		if (!empty()) {
			int i = 0;
			for (; buffer_[i] != *pos; i++);
			for (int j = i; j < size() - 2; j++) {
				buffer_[j] = buffer_[j + 1];
			}
			size_--;
			return iterator(++pos);
		} else throw VectorError();
	}
	iterator erase(iterator first, iterator last) {
		if (!empty()) {
			if (first == this->begin() && last == this->end()) {
				this->clear();
				return this->end();
			} else {
				while (first != last) {
					first = erase(first);
				}
				return iterator(last);
			}
		} else throw VectorError();
	}
	class const_iterator {
		T* index_;
	public:
		const_iterator(T* current) : index_(current) {}
		const T& operator*() {
			return *index_;
		}
		const_iterator operator++() {
			return const_iterator(++index_);
		}
		const_iterator operator++(int) {
			return const_iterator(index_++);
		}
		const_iterator operator--(int) {
			return const_iterator(index_--);
		}
		const_iterator operator--() {
			return const_iterator(--index_);
		}
		bool operator!=(const const_iterator& other) const {
			return index_ != other.index_;
		}
		bool operator==(const const_iterator& other) const {
			return index_ == other.index_;
		}
	};
	const_iterator cbegin() const {
		return &buffer_[0];
	}
	const_iterator cend() const {
		return &buffer_[size()];
	}
	class reverse_iterator {
		T* index_;
	public:
		reverse_iterator(T* index) : index_(index) {}
		T& operator*() {
			return *index_;
		}
		reverse_iterator operator++() {
			return reverse_iterator(--index_);
		}
		reverse_iterator operator++(int) {
			return reverse_iterator(index_--);
		}
		reverse_iterator operator--(int) {
			return reverse_iterator(index_++);
		}
		reverse_iterator operator--() {
			return reverse_iterator(++index_);
		}
		bool operator!=(const reverse_iterator& other) const {
			return index_ != other.index_;
		}
		bool operator==(const reverse_iterator& other) const {
			return index_ == other.index_;
		}
	};
	reverse_iterator rbegin() {
		return &buffer_[size() - 1];
	}
	reverse_iterator rend() {
		return &buffer_[-1];
	}
	class const_reverse_iterator {
		T* index_;
	public:
		const_reverse_iterator(T* index) : index_(index) {}
		const T& operator*() {
			return *index_;
		}
		const_reverse_iterator operator++() {
			return const_reverse_iterator(--index_);
		}
		const_reverse_iterator operator++(int) {
			return const_reverse_iterator(index_--);
		}
		const_reverse_iterator operator--(int) {
			return const_reverse_iterator(index_++);
		}
		const_reverse_iterator operator--() {
			return const_reverse_iterator(++index_);
		}
		bool operator!=(const const_reverse_iterator& other) const {
			return index_ != other.index_;
		}
		bool operator==(const const_reverse_iterator& other) const {
			return index_ == other.index_;
		}
	};
	const_reverse_iterator crbegin() const {
		return &buffer_[size() - 1];
	}
	const_reverse_iterator crend() const {
		return &buffer_[-1];
	}
};

template<class T>
ostream& operator<<(ostream& out, const Vector<T>& v) {
	out << ": {";
	for (typename Vector<T>::const_iterator it = v.cbegin(); it != v.cend(); it++) {
		out << *it << ",";
	}
	out << "}";
	return out;
}

int main(int argc, char* argv[]) {
	Vector<int> v1, v2;
	for (int i = atoi(argv[1]); i < atoi(argv[2]); i++) {
		v1.push_back(i);
	}
	for (int i = atoi(argv[3]); i < atoi(argv[4]); i++) {
		v2.push_back(i);
	}
	cout << "v1" << v1 << endl;
	cout << "v2" << v2 << endl;
	bool eq = false;
	for (Vector<int>::iterator it1 = v1.begin(), it2 = v2.begin();
		it1 != v1.end(), it2 != v2.end(); it1++, it2++) {
		if (*it1 == *it2) {
			cout << "equal element in v1 and v2: " << *it1 << endl;
			eq = true;
		}
	}
	if (!eq) {
		cout << "equal element in v1 and v2: 0" << endl;
	}
	v1.push_back(-100);
	v2.push_back(-100);
	cout << "v1" << v1 << endl;
	cout << "v2" << v2 << endl;
	Vector<int> v = v2;
	cout << "v" << v << endl;
	for (Vector<int>::reverse_iterator it = v1.rbegin(); it != v1.rend(); it++) {
		v.insert(v.begin(), *it);
	}
	cout << "v" << v << endl;
	for (Vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		if (*it == -100) {
			Vector<int>::iterator bit = it;
			v.erase(bit, v.end());
			break;
		}
	}
	cout << "v" << v << endl;
	return 0;
}