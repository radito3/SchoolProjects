#include <iostream>
#include <cstdlib>
#include <utility>

using namespace std;

class VectorError : public exception {
    const char* msg;
    
public:
    VectorError() : msg("") {}
    explicit VectorError(const char *msg) : msg(msg) {}
    
    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return msg;
    }
};

template<class T>
class Vector {
    static const int CAPACITY_GROWTH_BATCH_SIZE = 30;
    int capacity_;
    int size_;
    T *data_;

    void resize() {
        T *old_data_ = data_;
        capacity_ += CAPACITY_GROWTH_BATCH_SIZE;
        data_ = new T[capacity_];
        copy(old_data_, old_data_ + size_, data_);
        delete [] old_data_;
    }

public:
    explicit Vector(int capacity = 10) : capacity_(capacity),
                                         size_(0),
                                         data_(new T[capacity])
    {}

    ~Vector() {
        delete [] data_;
    }

    Vector(const Vector<T> &other) : size_(other.size_),
                                     capacity_(other.capacity_),
                                     data_(new T[other.capacity_]) {
        copy(other.data_, other.data_ + other.size_, data_);
    }

    Vector(Vector<T> &&other) noexcept : capacity_(exchange(other.capacity_, 0)),
                                         size_(exchange(other.size_, 0)),
                                         data_(exchange(other.data_, nullptr))
    {}

    Vector<T> &operator=(const Vector<T> &other) {
        if (this == addressof(other)) {
            return *this;
        }
        delete [] data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        data_ = new T[capacity_];
        copy(other.data_, other.data_ + other.size_, data_);
        return *this;
    }

    Vector<T> &operator=(Vector<T> &&other) noexcept {
        if (this == addressof(other)) {
            return *this;
        }
        delete [] data_;
        capacity_ = exchange(other.capacity_, 0);
        size_ = exchange(other.size_, 0);
        data_ = exchange(other.data_, nullptr);
        return *this;
    }

    bool empty() const {
        return size_ == 0;
    }

    int size() const {
        return size_;
    }

    T &operator[](int n) {
        if (n > size_) {
            throw VectorError("Vector<T>::operator[]: n is larger than size");
        }
        return data_[n];
    }

    const T &operator[](int n) const {
        if (n > size_) {
            throw VectorError("Vector<T>::operator[]: n is larger than size");
        }
        return data_[n];
    }

    void clear() {
        if (!empty()) {
            delete[] data_;
            size_ = 0;
        }
    }

    int capacity() const {
        return capacity_;
    }

    T &front() {
        return data_[0];
    }

    const T &front() const {
        return data_[0];
    }

    T &back() {
        return data_[size_ - 1];
    }

    const T &back() const {
        return data_[size_ - 1];
    }

    void push_back(const T &val) {
        if (size_ + 1 > capacity_) {
            resize();
        }
        data_[size_++] = val;
    }

    void pop_back() {
        if (empty()) {
            throw VectorError("Vector<T>::pop_back: vector is empty");
        }
        data_[size_ - 1] = nullptr;
        size_--;
    }

    class iterator {
        T *elem_;
    public:
        explicit iterator(T *elem) : elem_(elem) {}

        T &operator*() const {
            return *elem_;
        }

        T *operator->() const {
            return elem_;
        }

        iterator operator++() {
            ++elem_;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            elem_++;
            return tmp;
        }

        iterator operator--(int) {
            iterator tmp = *this;
            elem_--;
            return tmp;
        }

        iterator operator--() {
            --elem_;
            return *this;
        }

        iterator operator+(int x) {
            iterator tmp = *this;
            elem_ += x;
            return tmp;
        }

        bool operator!=(const iterator &other) const {
            return elem_ != other.elem_;
        }

        bool operator==(const iterator &other) const {
            return elem_ == other.elem_;
        }
    };

    iterator begin() const {
        return iterator(data_);
    }

    iterator end() const {
        return iterator(data_ + size_);
    }

    int where(iterator pos) const {
        if (empty()) {
            return -1;
        }
        iterator it = begin();
        int i = 0;
        while (i < size_ && it != pos) {
            i++;
            it++;
        }
        return i >= size_ ? -1 : i;
    }

    iterator insert(iterator pos, const T &x) {
        if (size_ + 1 > capacity_) {
            resize();
        }
        int idx_of_iter = where(pos);
        T* tmp = new T[size_ - idx_of_iter];
        copy(data_ + idx_of_iter, data_ + size_, tmp);
        data_[idx_of_iter] = x;
        size_++;
        copy(tmp, tmp + (size_ - idx_of_iter), data_ + (idx_of_iter + 1));
        delete [] tmp;
        return iterator(data_ + (idx_of_iter + 1));
    }

    iterator erase(iterator pos) {
        if (empty()) {
            throw VectorError("Vector<T>::erase: vector is empty");
        }
        int idx_of_iter = where(pos);
        if (idx_of_iter == -1) {
            throw VectorError("Vector<T>::erase: invalid iterator");
        }
        data_[idx_of_iter] = NULL;
        copy(data_ + (idx_of_iter + 1), data_ + size_, data_ + idx_of_iter);
        size_--;
        return iterator(data_ + idx_of_iter);
    }

    iterator erase(iterator first, iterator last) {
        if (empty()) {
            throw VectorError("Vector<T>::erase: vector is empty");
        }
        //something here is not right...
        while (first != last) { 
            first = erase(first);
        }
        return iterator(last);
    }

    class const_iterator {
        const T *elem_;
    public:
        explicit const_iterator(const T *elem) : elem_(elem) {}

        const T &operator*() const {
            return *elem_;
        }

        const T *operator->() const {
            return elem_;
        }

        const_iterator operator++() {
            ++elem_;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator tmp = *this;
            elem_++;
            return tmp;
        }

        const_iterator operator--(int) {
            const_iterator tmp = *this;
            elem_--;
            return tmp;
        }

        const_iterator operator--() {
            --elem_;
            return *this;
        }

        bool operator!=(const const_iterator &other) const {
            return elem_ != other.elem_;
        }

        bool operator==(const const_iterator &other) const {
            return elem_ == other.elem_;
        }
    };

    const_iterator cbegin() const {
        return const_iterator(data_);
    }

    const_iterator cend() const {
        return const_iterator(data_ + size_);
    }

    class reverse_iterator {
        T *elem_;
    public:
        explicit reverse_iterator(T *elem) : elem_(elem) {}

        T &operator*() const {
            return *elem_;
        }

        T *operator->() const {
            return elem_;
        }

        reverse_iterator operator++() {
            --elem_;
            return *this;
        }

        reverse_iterator operator++(int) {
            reverse_iterator tmp = *this;
            elem_--;
            return tmp;
        }

        reverse_iterator operator--(int) {
            reverse_iterator tmp = *this;
            elem_++;
            return tmp;
        }

        reverse_iterator operator--() {
            ++elem_;
            return *this;
        }

        bool operator!=(const reverse_iterator &other) const {
            return elem_ != other.elem_;
        }

        bool operator==(const reverse_iterator &other) const {
            return elem_ == other.elem_;
        }
    };

    reverse_iterator rbegin() const {
        return reverse_iterator(data_ + ((size_ > 0 ? size_ : 1) - 1));
    }

    reverse_iterator rend() const {
        return reverse_iterator(data_ - 1);
    }

    class const_reverse_iterator {
        T *elem_;
    public:
        explicit const_reverse_iterator(T *elem) : elem_(elem) {}

        const T &operator*() const {
            return *elem_;
        }

        const T *operator->() const {
            return elem_;
        }

        const_reverse_iterator operator++() {
            --elem_;
            return *this;
        }

        const_reverse_iterator operator++(int) {
            return const_reverse_iterator(elem_--);
        }

        const_reverse_iterator operator--(int) {
            return const_reverse_iterator(elem_++);
        }

        const_reverse_iterator operator--() {
            ++elem_;
            return *this;
        }

        bool operator!=(const const_reverse_iterator &other) const {
            return elem_ != other.elem_;
        }

        bool operator==(const const_reverse_iterator &other) const {
            return elem_ == other.elem_;
        }
    };

    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(data_ + ((size_ > 0 ? size_ : 1) - 1));
    }

    const_reverse_iterator crend() const {
        return const_reverse_iterator(data_ - 1);
    }
};

template<class T>
ostream &operator<<(ostream &out, const Vector<T> &v) {
    for (typename Vector<T>::const_iterator it = v.cbegin(); it != v.cend(); it++) {
        out << *it << ",";
    }
    return out;
}

int main(int argc, char *argv[]) {
    Vector<int> v1, v2;
    for (int i = atoi(argv[1]); i < atoi(argv[2]); i++) {
        v1.push_back(i);
    }
    for (int i = atoi(argv[3]); i < atoi(argv[4]); i++) {
        v2.push_back(i);
    }

    cout << "v1: {" << v1 << '}' << endl;
    cout << "v2: {" << v2 << '}' << endl;

    bool eq = false;
    for (auto el : v1) {
        for (auto el2 : v2) {
            if (el == el2) {
                cout << "equal element in v1 and v2: " << el << endl;
                eq = true;
            }
        }
    }
    if (!eq) {
        cout << "no equal elements in v1 and v2" << endl;
    }

    v1.push_back(-100);
    v2.push_back(-100);

    cout << "v1: {" << v1 << '}' << endl;
    cout << "v2: {" << v2 << '}' << endl;

    Vector<int> v;
    v = v2;
    cout << "v: {" << v << '}' << endl;
    for (Vector<int>::reverse_iterator it = v1.rbegin(); it != v1.rend(); it++) {
        v.insert(v.begin(), *it);
    }

    cout << "-v: {" << v << '}' << endl;
    v.erase(v.begin());
    cout << "--v: {" << v << '}' << endl;
    v.erase(--v.end());
    cout << "---v: {" << v << '}' << endl;

    for (Vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        if (*it == -100) {
            v.erase(it, v.end());
            break;
        }
    }

    cout << "v: {" << v << '}' << endl;
    return 0;
}
