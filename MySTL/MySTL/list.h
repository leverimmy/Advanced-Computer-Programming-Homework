#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <initializer_list>
#include <typeinfo>

template <typename T> class list {
public:
    list();
    list(const std::initializer_list<T>& list);
    list(const list<T>& rhs);
    ~list();
    void push_back(const T& val);
    void push_front(const T& val);
    void pop_back();
    void pop_front();
    T& back();
    T& front();
    bool empty() const;
    size_t size() const;
    void clear();
    
    bool operator==(const list<T>& rhs) const;
    list<T>& operator=(const list<T>& rhs);

private:
    struct Node {
        T data;
        Node* nxt;
        Node* pre;
    };
    Node* m_head;
    Node* m_tail;
    size_t m_size;
};

#endif // LIST_H
