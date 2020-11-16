#include <iostream>
#include <algorithm>
#include <memory>
#include <stdexcept>

using namespace std;

template <typename T>
class Stack {
    size_t top_;
    size_t capacity_;
    T* data_;

    static const size_t CHUNK_SIZE = 15;

    void resize() {
        T* old_data = data_;
        capacity_ += CHUNK_SIZE;
        data_ = new T[capacity_];
        copy(old_data, old_data + top_, data_);
        delete [] old_data;
    }

public:
    Stack() : top_(0), capacity_(CHUNK_SIZE), data_(new T[capacity_]) {}

    Stack(const initializer_list<T>& list) : top_(list.size()), capacity_(list.size() + CHUNK_SIZE), data_(new T[capacity_]) {
        copy(list.begin(), list.end(), data_);
    }

    Stack(const Stack& other) : top_(other.top_), capacity_(other.capacity_), data_(new T[capacity_]) {
        copy(other.data_, other.data_ + other.top_, data_);
    }

    ~Stack() {
        delete [] data_;
    }

    Stack& operator=(const Stack& other) {
        if (this != addressof(other)) {
            delete [] data_;
            top_ = other.top_;
            capacity_ = other.capacity_;
            data_ = new T[capacity_];
            copy(other.data_, other.data_ + top_, data_);
        }
        return *this;
    }

    bool empty() const {
        return top_ == 0;
    }

    void push(const T& val) {
        if (top_ == capacity_) {
            resize();
        }
        data_[top_++] = val;
    }

    T& pop() {
        if (empty()) {
            throw runtime_error("empty stack");
        }
        return data_[--top_];
    }
};

int main() {
    Stack<int> st;
    cout << boolalpha << st.empty() << noboolalpha << endl;
    for (int i = 0; i < 10; ++i) {
        st.push(i * 42);
    }
    Stack<int> st1 = st;
    while (!st1.empty()) {
        cout << "st1: " << st1.pop() << endl;
    }
    Stack<int> st2;
    st2 = st;
    while (!st2.empty()) {
        cout << "st2: " << st2.pop() << endl;
    }
    st = st;
    while (!st.empty()) {
        cout << st.pop() << endl;
    }
    return 0;
}
