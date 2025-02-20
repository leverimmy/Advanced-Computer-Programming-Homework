#include "BallList.h"
#include <stdexcept>

BallList::BallNode::BallNode(const Ball& ball, BallNode* next)
    : ball(ball), next(next) {}

BallList::BallList() : head(nullptr), m_size(0) {}

BallList::~BallList() {
    clear();
}

void BallList::append(const Ball& ball) {
    BallNode* newNode = new BallNode(ball, nullptr);
    if (head == nullptr) {
        head = newNode;
    } else {
        BallNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    m_size++;
}

void BallList::insert(int index, const Ball& ball) {
    if (index < 0 || index > m_size) {
        return;
    }
    BallNode* newNode = new BallNode(ball, nullptr);
    if (index == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        BallNode* current = head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    m_size++;
}

void BallList::erase(BallNode* begin, BallNode* end) {
    if (begin == head) {
        head = end;
    } else {
        BallNode* current = head;
        while (current->next != begin) {
            current = current->next;
        }
        current->next = end;
    }
    while (begin != end) {
        BallNode* next = begin->next;
        delete begin;
        begin = next;
        m_size--;
    }
}

Ball& BallList::operator[](int index) {
    if (index < 0 || index >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    BallNode* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->ball;
}

void BallList::clear() {
    while (head != nullptr) {
        BallNode* next = head->next;
        delete head;
        head = next;
    }
    m_size = 0;
}

Ball& BallList::last() {
    if (head == nullptr) {
        throw std::out_of_range("List is empty");
    }
    BallNode* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current->ball;
}

bool BallList::isEmpty() const {
    return m_size == 0;
}

int BallList::size() const {
    return m_size;
}
