#ifndef QUEUE_H
#define QUEUE_H

#include "deque.cpp"

template <typename T> class queue {
public:
    queue();
    queue(const std::initializer_list<T>& list);
    queue(const queue<T>& rhs);
    ~queue();
    void push(const T& val);
    void pop();
    T& front();
    T& back();
    bool empty() const;
    size_t size() const;
    void clear();

    bool operator==(const queue<T>& rhs) const;
    queue<T>& operator=(const queue<T>& rhs);

private:
    deque<T>* _container;
};

#endif // QUEUE_H
