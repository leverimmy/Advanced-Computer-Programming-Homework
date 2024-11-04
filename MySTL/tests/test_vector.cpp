#include "../MySTL/vector.cpp"
#include <cassert>
#include <iostream>

int main() {
    // 测试默认构造函数和 empty 方法
    vector<int> v;
    assert(v.empty() == true);
    assert(v.size() == 0);

    // 测试 initializer_list 构造函数
    vector<int> v2 = {1, 2, 3};
    assert(v2.size() == 3);
    assert(v2.back() == 3);

    // 测试拷贝构造函数
    vector<int> v3 = v2;
    assert(v3 == v2);

    // 测试赋值操作符
    vector<int> v4;
    v4 = v2;
    assert(v4 == v2);

    // 测试 push_back 方法
    v4.push_back(4);
    assert(v4.size() == 4);
    assert(v4.back() == 4);

    // 测试 pop_back 方法
    v4.pop_back();
    assert(v4.size() == 3);
    assert(v4.back() == 3);

    // 测试 back 方法
    assert(v4.back() == 3);

    // 测试 clear 方法
    v4.clear();
    assert(v4.empty() == true);
    assert(v4.size() == 0);

    // 测试 [] 操作符
    v2[0] = 10;
    assert(v2[0] == 10);

    // 测试 == 操作符
    assert(!(v2 == v3));

    std::cout << "All tests passed for vector!" << std::endl;
    return 0;
}
