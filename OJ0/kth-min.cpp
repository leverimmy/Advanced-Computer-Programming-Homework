#include <iostream>
#include <vector>
#include <algorithm> // 用于 std::sort

int main() {
    int n, k;
    std::cin >> n >> k; // 读取数组长度和k的值

    std::vector<int> arr(n); // 创建一个向量来存储数组元素
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i]; // 读取数组元素
    }

    // 对数组进行排序
    std::sort(arr.begin(), arr.end());

    // 输出第k小的数，由于数组索引从0开始，所以是k-1
    std::cout << arr[k - 1] << std::endl;

    return 0;
}