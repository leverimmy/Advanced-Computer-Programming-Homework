#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    for (string s; getline(cin, s); ) {  // 遍历输入的每一行
        bool first = true;  // 是否是当前行的第一个整数
        size_t n = s.size();
        for (size_t i = 0; i < n; i++)
            if (s[i] >= '0' && s[i] <= '9') {
                // s[i] 是一个数字
                // 下面寻找以 s[i] 开始的连续一段数字的结尾在哪里
                size_t r = i + 1;
                while (s[r] >= '0' && s[r] <= '9')
                    ++r;
                // 到目前为止，找到了以 s[i] 开始，s[r] 结束的一段数字
                // 此时 s[r] 是数字，s[r + 1] 不是数字

                // 如果不是当前行的第一个整数，则先输出一个空格
                if (first)
                    first = false;
                else
                    putchar(' ');

                // 输出当前整数
                for (size_t j = i; j < r; j++)
                    putchar(s[j]);

                // 跳过当前已输出完毕的整数
                // 这样在输出 1234 以后不会再输出 234 和 34，而是从 4 后面寻找下一个数
                i = r;
            }
        putchar('\n');
    }
    return 0;
}
