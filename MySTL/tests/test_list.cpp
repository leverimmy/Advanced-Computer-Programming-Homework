#include "../MySTL/list.cpp"
#include <cassert>
#include <iostream>

int main() {
    // 测试构造函数和 empty 方法
    list<int> l;
    assert(l.empty() == true);
    assert(l.size() == 0);

    // 测试 push_back 和 size 方法
    l.push_back(1);
    assert(l.size() == 1);
    assert(l.back() == 1);

    // 测试 push_front 和 size 方法
    l.push_front(0);
    assert(l.size() == 2);
    assert(l.front() == 0);

    // 测试 back 和 front 方法
    assert(l.back() == 1);
    assert(l.front() == 0);

    // 测试 pop_back 和 empty 方法
    l.pop_back();
    assert(l.size() == 1);
    assert(l.back() == 0);
    assert(l.empty() == false);

    // 测试 pop_front 和 empty 方法
    l.pop_front();
    assert(l.size() == 0);
    assert(l.empty() == true);

    // 测试 clear 方法
    l.push_back(2);
    l.push_back(3);
    l.clear();
    assert(l.empty() == true);
    assert(l.size() == 0);

    // 测试 operator== 方法
    list<int> l2;
    l2.push_back(2);
    l2.push_back(3);
    assert(!(l == l2));

    // 测试拷贝构造函数和赋值操作符
    list<int> l3 = l2;
    assert(l3 == l2);

    // 测试赋值操作符
    list<int> l4;
    l4 = l2;
    assert(l4 == l2);

    std::cout << "All tests passed for list!" << std::endl;
    return 0;
}
