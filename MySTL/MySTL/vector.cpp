#include "vector.h"

template <typename T> vector<T>::vector() {
    _container = new T[1];
    _size = 0;
    _capacity = 1;
}

template <typename T> vector<T>::vector(const std::initializer_list<T>& list) {
    _container = new T[list.size()];
    _size = 0;
    _capacity = list.size();
    for (const T& val : list) {
        push_back(val);
    }
}

template <typename T> vector<T>::vector(const vector<T>& rhs) {
    _container = new T[rhs._capacity];
    _size = rhs._size;
    _capacity = rhs._capacity;
    for (size_t i = 0; i < _size; ++i) {
        _container[i] = rhs._container[i];
    }
}

template <typename T> vector<T>::~vector() {
    delete[] _container;
}

template <typename T> void vector<T>::push_back(const T& val) {
    if (_size == _capacity) {
        resize();
    }
    _container[_size++] = val;
}

template <typename T> void vector<T>::pop_back() {
    if (_size > 0) {
        --_size;
    }
}

template <typename T> T& vector<T>::back() {
    return _container[_size - 1];
}

template <typename T> bool vector<T>::empty() const {
    return _size == 0;
}

template <typename T> size_t vector<T>::size() const {
    return _size;
}

template <typename T> void vector<T>::clear() {
    _size = 0;
}

template <typename T> T& vector<T>::operator[](size_t index) {
    return _container[index];
}

template <typename T> bool vector<T>::operator==(const vector<T>& rhs) const {
    if (_size != rhs._size) {
        return false;
    }
    for (size_t i = 0; i < _size; ++i) {
        if (_container[i] != rhs._container[i]) {
            return false;
        }
    }
    return true;
}

template <typename T> vector<T>& vector<T>::operator=(const vector<T>& rhs) {
    if (this == &rhs) {
        return *this;
    }
    delete[] _container;
    _container = new T[rhs._capacity];
    _size = rhs._size;
    _capacity = rhs._capacity;
    for (size_t i = 0; i < _size; ++i) {
        _container[i] = rhs._container[i];
    }
    return *this;
}

template <typename T> void vector<T>::resize() {
    T* new_container = new T[_capacity * 2];
    for (size_t i = 0; i < _size; ++i) {
        new_container[i] = _container[i];
    }
    delete[] _container;
    _container = new_container;
    _capacity *= 2;
}

