#include "stack.h"

template <typename T> stack<T>::stack() {
    _container = new deque<T>();
}

template <typename T> stack<T>::stack(const std::initializer_list<T>& list) {
    _container = new deque<T>(list);
}

template <typename T> stack<T>::stack(const stack<T>& rhs) {
    _container = rhs._container;
}

template <typename T> stack<T>::~stack() {
    _container->clear();
}

template <typename T> void stack<T>::push(const T& val) {
    _container->push_back(val);
}

template <typename T> void stack<T>::pop() {
    _container->pop_back();
}

template <typename T> T& stack<T>::top() {
    return _container->back();
}

template <typename T> bool stack<T>::empty() const {
    return _container->empty();
}

template <typename T> size_t stack<T>::size() const {
    return _container->size();
}

template <typename T> void stack<T>::clear() {
    _container->clear();
}

template <typename T> bool stack<T>::operator==(const stack<T>& rhs) const {
    if (typeid(*_container) != typeid(*rhs._container)) {
        return false;
    }
    return *_container == *rhs._container;
}

template <typename T> stack<T>& stack<T>::operator=(const stack<T>& rhs) {
    _container = rhs._container;
    return *this;
}
