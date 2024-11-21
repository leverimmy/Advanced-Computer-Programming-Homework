#ifndef BALLLIST_H
#define BALLLIST_H

#include "Ball.h"

class BallList {
public:
    struct BallNode {
        Ball ball;
        BallNode* next;
        BallNode(const Ball& ball, BallNode* next);
    };

    BallNode* head;

    BallList();
    ~BallList();

    void append(const Ball& ball);
    void insert(int index, const Ball& ball);
    void erase(BallNode* begin, BallNode* end);
    Ball& operator[](int index);
    void clear();
    Ball& last();
    bool isEmpty() const;
    int size() const;

private:
    int m_size;
};

#endif // BALLLIST_H
