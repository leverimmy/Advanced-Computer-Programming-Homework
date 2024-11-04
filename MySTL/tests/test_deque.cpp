#include "../MySTL/deque.cpp"
#include <cassert>
#include <iostream>

int main() {
    // 测试默认构造函数和 empty 方法
    deque<int> dq;
    assert(dq.empty() == true);
    assert(dq.size() == 0);

    // 测试 initializer_list 构造函数
    deque<int> dq2 = {1, 2, 3};
    assert(dq2.size() == 3);
    assert(dq2.front() == 1);
    assert(dq2.back() == 3);

    // 测试拷贝构造函数
    deque<int> dq3 = dq2;
    assert(dq3 == dq2);

    // 测试赋值操作符
    deque<int> dq4;
    dq4 = dq2;
    assert(dq4 == dq2);

    // 测试 push_back 和 back 方法
    dq4.push_back(4);
    assert(dq4.size() == 4);
    assert(dq4.back() == 4);

    // 测试 push_front 和 front 方法
    dq4.push_front(0);
    assert(dq4.size() == 5);
    assert(dq4.front() == 0);

    // 测试 pop_back 和 back 方法
    dq4.pop_back();
    assert(dq4.size() == 4);
    assert(dq4.back() == 3);

    // 测试 pop_front 和 front 方法
    dq4.pop_front();
    assert(dq4.size() == 3);
    assert(dq4.front() == 1);

    // 测试 clear 方法
    dq4.clear();
    assert(dq4.empty() == true);
    assert(dq4.size() == 0);

    std::cout << "All tests passed for deque!" << std::endl;
    return 0;
}
