#include "queue.h"

template <typename T> queue<T>::queue() {
    _container = new deque<T>();
}

template <typename T> queue<T>::queue(const std::initializer_list<T>& list) {
    _container = new deque<T>(list);
}

template <typename T> queue<T>::queue(const queue<T>& rhs) {
    _container = rhs._container;
}

template <typename T> queue<T>::~queue() {
    _container->clear();
}

template <typename T> void queue<T>::push(const T& val) {
    _container->push_back(val);
}

template <typename T> void queue<T>::pop() {
    _container->pop_front();
}

template <typename T> T& queue<T>::front() {
    return _container->front();
}

template <typename T> T& queue<T>::back() {
    return _container->back();
}

template <typename T> bool queue<T>::empty() const {
    return _container->empty();
}

template <typename T> size_t queue<T>::size() const {
    return _container->size();
}

template <typename T> void queue<T>::clear() {
    _container->clear();
}

template <typename T> bool queue<T>::operator==(const queue<T>& rhs) const {
    if (typeid(*_container) != typeid(*rhs._container)) {
        return false;
    }
    return *_container == *rhs._container;
}

template <typename T> queue<T>& queue<T>::operator=(const queue<T>& rhs) {
    _container = rhs._container;
    return *this;
}
