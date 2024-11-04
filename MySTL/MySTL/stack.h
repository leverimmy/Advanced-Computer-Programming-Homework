#ifndef STACK_H
#define STACK_H

#include "deque.cpp"

template <typename T> class stack {
public:
    stack();
    stack(const std::initializer_list<T>& list);
    stack(const stack<T>& rhs);
    ~stack();
    void push(const T& val);
    void pop();
    T& top();
    bool empty() const;
    size_t size() const;
    void clear();

    bool operator==(const stack<T>& rhs) const;
    stack<T>& operator=(const stack<T>& rhs);

private:
    deque<T>* _container;
};

#endif // STACK_H
