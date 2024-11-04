#include "../MySTL/queue.cpp"
#include <cassert>
#include <iostream>

int main() {
    // 测试默认构造函数和 empty 方法
    queue<int> q;
    assert(q.empty() == true);
    assert(q.size() == 0);

    // 测试 initializer_list 构造函数
    queue<int> q2 = {1, 2, 3};
    assert(q2.size() == 3);
    assert(q2.front() == 1);
    assert(q2.back() == 3);

    // 测试拷贝构造函数
    queue<int> q3 = q2;
    assert(q3 == q2);

    // 测试赋值操作符
    queue<int> q4;
    q4 = q2;
    assert(q4 == q2);

    // 测试 push 方法
    q4.push(4);
    assert(q4.size() == 4);
    assert(q4.back() == 4);

    // 测试 pop 方法
    q4.pop();
    assert(q4.size() == 3);
    assert(q4.front() == 2);

    // 测试 front 和 back 方法
    assert(q4.front() == 2);
    assert(q4.back() == 4);

    // 测试 clear 方法
    q4.clear();
    assert(q4.empty() == true);
    assert(q4.size() == 0);

    std::cout << "All tests passed for queue!" << std::endl;
    return 0;
}
