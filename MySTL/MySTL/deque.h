#ifndef DEQUE_H
#define DEQUE_H

#include "list.cpp"

template <typename T> class deque {
public:
    deque();
    deque(const std::initializer_list<T>& list);
    deque(const deque<T>& rhs);
    ~deque();
    void push_back(const T& val);
    void push_front(const T& val);
    void pop_back();
    void pop_front();
    T& back();
    T& front();
    bool empty() const;
    size_t size() const;
    void clear();

    bool operator==(const deque<T>& rhs) const;
    deque<T>& operator=(const deque<T>& rhs);

private:
    list<T>* _container;
};

#endif
