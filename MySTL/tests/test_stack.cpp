#include "../MySTL/stack.cpp"
#include <cassert>
#include <iostream>

int main() {
    // 测试默认构造函数和 empty 方法
    stack<int> s;
    assert(s.empty() == true);
    assert(s.size() == 0);

    // 测试 initializer_list 构造函数
    stack<int> s2 = {1, 2, 3};
    assert(s2.size() == 3);
    assert(s2.top() == 3); // 栈顶元素应为最后一个元素

    // 测试拷贝构造函数
    stack<int> s3 = s2;
    assert(s3 == s2);

    // 测试赋值操作符
    stack<int> s4;
    s4 = s2;
    assert(s4 == s2);

    // 测试 push 方法
    s4.push(4);
    assert(s4.size() == 4);
    assert(s4.top() == 4); // 新栈顶元素应为4

    // 测试 pop 方法
    s4.pop();
    assert(s4.size() == 3);
    assert(s4.top() == 3); // 栈顶元素应为3

    // 测试 top 方法
    assert(s4.top() == 3);

    // 测试 clear 方法
    s4.clear();
    assert(s4.empty() == true);
    assert(s4.size() == 0);

    std::cout << "All tests passed for stack!" << std::endl;
    return 0;
}
