#include "list.h"

template <typename T> list<T>::list() {
    m_head = new Node();
    m_tail = new Node();
    m_head->nxt = m_tail;
    m_tail->pre = m_head;
    m_size = 0;
}

template <typename T> list<T>::list(const std::initializer_list<T>& list) {
    m_head = new Node();
    m_tail = new Node();
    m_head->nxt = m_tail;
    m_tail->pre = m_head;
    m_size = 0;
    for (const T& val : list) {
        push_back(val);
    }
}

template <typename T> list<T>::list(const list<T>& rhs) {
    m_head = new Node();
    m_tail = new Node();
    m_head->nxt = m_tail;
    m_tail->pre = m_head;
    m_size = 0;
    Node* cur = rhs.m_head->nxt;
    while (cur != rhs.m_tail) {
        push_back(cur->data);
        cur = cur->nxt;
    }
}

template <typename T> list<T>::~list() {
    clear();
    delete m_head;
    delete m_tail;
}

template <typename T> void list<T>::push_back(const T& val) {
    Node* new_node = new Node();
    new_node->data = val;
    new_node->nxt = m_tail;
    new_node->pre = m_tail->pre;
    m_tail->pre->nxt = new_node;
    m_tail->pre = new_node;
    ++m_size;
}

template <typename T> void list<T>::push_front(const T& val) {
    Node* new_node = new Node();
    new_node->data = val;
    new_node->nxt = m_head->nxt;
    new_node->pre = m_head;
    m_head->nxt->pre = new_node;
    m_head->nxt = new_node;
    ++m_size;
}

template <typename T> void list<T>::pop_back() {
    if (m_size == 0) return;
    Node* del_node = m_tail->pre;
    m_tail->pre = del_node->pre;
    del_node->pre->nxt = m_tail;
    delete del_node;
    --m_size;
}

template <typename T> void list<T>::pop_front() {
    if (m_size == 0) return;
    Node* del_node = m_head->nxt;
    m_head->nxt = del_node->nxt;
    del_node->nxt->pre = m_head;
    delete del_node;
    --m_size;
}

template <typename T> T& list<T>::back() {
    return m_tail->pre->data;
}

template <typename T> T& list<T>::front() {
    return m_head->nxt->data;
}

template <typename T> bool list<T>::empty() const {
    return m_size == 0;
}

template <typename T> size_t list<T>::size() const {
    return m_size;
}

template <typename T> void list<T>::clear() {
    while (m_size > 0) {
        pop_back();
    }
}

template <typename T> bool list<T>::operator==(const list<T>& rhs) const {
    if (m_size != rhs.m_size) return false;
    Node* cur1 = m_head->nxt;
    Node* cur2 = rhs.m_head->nxt;
    while (cur1 != m_tail) {
        if (cur1->data != cur2->data) return false;
        cur1 = cur1->nxt;
        cur2 = cur2->nxt;
    }
    return true;
}

template <typename T> list<T>& list<T>::operator=(const list<T>& rhs) {
    if (this == &rhs) return *this;
    clear();
    Node* cur = rhs.m_head->nxt;
    while (cur != rhs.m_tail) {
        push_back(cur->data);
        cur = cur->nxt;
    }
    return *this;
}
