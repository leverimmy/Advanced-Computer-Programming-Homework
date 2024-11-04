#include "deque.h"

template <typename T> deque<T>::deque() {
    _container = new list<T>();
}

template <typename T> deque<T>::deque(const std::initializer_list<T>& l) {
    _container = new list<T>(l);
}

template <typename T> deque<T>::deque(const deque<T>& rhs) {
    _container = rhs._container;
}

template <typename T> deque<T>::~deque() {
    _container->clear();
}

template <typename T> void deque<T>::push_back(const T& val) {
    _container->push_back(val);
}

template <typename T> void deque<T>::push_front(const T& val) {
    _container->push_front(val);
}

template <typename T> void deque<T>::pop_back() {
    _container->pop_back();
}

template <typename T> void deque<T>::pop_front() {
    _container->pop_front();
}

template <typename T> T& deque<T>::back() {
    return _container->back();
}

template <typename T> T& deque<T>::front() {
    return _container->front();
}

template <typename T> bool deque<T>::empty() const {
    return _container->empty();
}

template <typename T> size_t deque<T>::size() const {
    return _container->size();
}

template <typename T> void deque<T>::clear() {
    _container->clear();
}

template <typename T> bool deque<T>::operator==(const deque<T>& rhs) const {
    if (typeid(*_container) != typeid(*rhs._container)) {
        return false;
    }
    return *_container == *rhs._container;
}

template <typename T> deque<T>& deque<T>::operator=(const deque<T>& rhs) {
    _container = rhs._container;
    return *this;
}
