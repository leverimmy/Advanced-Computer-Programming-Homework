# OJ1

## Wrong Number

这题比较简单，需要实现的功能是提取输入文本中的非负整数。

我直接将题目文字复制粘贴到 [Kimi.ai - 帮你看更大的世界](https://kimi.moonshot.cn/) 的对话框中。**我没有添加任何其余的 prompt**。AI 写的代码如下：

```cpp
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    for (string s; getline(cin, s); ) {  // 遍历输入的每一行
        bool isFirst = true;  // 是否是当前行的第一个整数
        size_t n = s.size();
        for (size_t i = 0; i < n; ) {
            if (isdigit(s[i])) {  // s[i] 是一个数字
                // 下面寻找以 s[i] 开始的连续一段数字的结尾在哪里
                size_t r = i;
                while (r < n && isdigit(s[r])) ++r;
                // 到目前为止，找到了以 s[i] 开始，s[r] 结束的一段数字
                // 此时 s[r] 是数字，s[r + 1] 不是数字

                // 如果不是当前行的第一个整数，则先输出一个空格
                if (!isFirst) {
                    putchar(' ');
                } else {
                    isFirst = false;
                }

                // 输出当前整数
                for (size_t j = i; j < r; j++) {
                    putchar(s[j]);
                }

                // 跳过当前已输出完毕的整数
                // 这样在输出 1234 以后不会再输出 234 和 34，而是从 4 后面寻找下一个数
                i = r;
            } else {
                ++i;
            }
        }
        putchar('\n');
    }
    return 0;
}
```

AI 找到了代码中的两个错误：`first` 没有赋初值和 `if (s[i] >= 0 && s[i] <= 9)` 应该改为 `if (isdigit(s[i]))`。我觉得很有意思的一点是，AI 采用了不那么容易出错的方式来实现判断 `s[i]` 是否为一个数字——使用 `isdigit()`，这样就不会像错误的代码一样忘记加单引号表示字符（`'0'` 和 `'9'`）。

我和 AI 之间的对话如下：[对话链接](https://kimi.moonshot.cn/share/crqksdecp7f60vbc6g30)

## Wrong Drink

题目给出 $n$ 种酒，对应着平面上的 $n$ 个点，要求求出它们构成的一个下凸壳。对于每个查询操作, 一定是使用该下凸壳上相邻的两种酒进行混合, 从而保证价格最低。

我仍然直接将题目文字复制粘贴到 [Kimi.ai - 帮你看更大的世界](https://kimi.moonshot.cn/) 的对话框中，要求其提供一个 C++ 代码解决此问题。AI 写的代码如下：

```cpp
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

typedef pair<int, int> dpair;

struct Wine {
    int d, p;
    Wine* last;

    static int counter;
    Wine() : last(nullptr) {
        ++counter;
    }
    ~Wine() {
        --counter;
    }
};

int Wine::counter = 0;

// 内存检查器, 请勿修改
struct Checker {
    int _;
    ~Checker() {
        if (Wine::counter != 0) {
            cout << "你的对象没有正确释放!\n";
        }
    }
} _c;

int main() {
    int n, m;
    vector<dpair> wines;
    vector<int> qs;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        int d, p;
        scanf("%d%d", &d, &p);
        wines.push_back(dpair(d, p));
    }
    // 按照浓度排序
    sort(wines.begin(), wines.end());

    Wine* head = nullptr; // 链表头节点
    Wine* tail = nullptr;
    for (int i = 0; i < n; ++i) {
        auto q = new Wine;
        q->d = wines[i].first;
        q->p = wines[i].second;
        while (head && tail && ((q->p - head->p) / (q->d - head->d) >= (tail->p - head->p) / (tail->d - head->d))) {
            head = head->last;
        }
        q->last = head;
        head = q;
        if (!head->last) {
            head->last = tail;
            if (tail) {
                tail->last = head;
            }
            tail = head;
        }
    }

    // 将链表转换回数组以便二分查找
    wines.clear();
    for (Wine* i = tail; i; i = i->last) {
        wines.push_back(dpair(i->d, i->p));
    }
    reverse(wines.begin(), wines.end());

    for (int i = 0; i < m; ++i) {
        int q;
        scanf("%d", &q);
        auto it = lower_bound(wines.begin(), wines.end(), dpair(q, INT_MAX));
        if (it == wines.end() || it->first > q) {
            printf("%.2lf\n", -1.0);
        } else {
            auto ib = it - 1;
            double res = (it->first - q) / (double)(it->first - ib->first) * ib->second;
            res += (q - ib->first) / (double)(it->first - ib->first) * it->second;
            printf("%.2lf\n", res);
        }
    }

    // 释放内存
    for (Wine* i = tail; i; ) {
        Wine* temp = i;
        i = i->last;
        delete temp;
    }
    return 0;
}
```

可惜的是，这份代码并不能通过编译。我尝试向 AI 提供编译报错信息，AI 给出了正确答案：

```cpp
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

typedef pair<int, int> dpair;

struct Wine {
    int d, p;
    Wine* last;

    static int counter;
    Wine() {
        ++counter;
    }
    ~Wine() {
        --counter;
    }
};

int Wine::counter = 0;

// 内存检查器, 请勿修改
struct Checker {
    int _;
    ~Checker() {
        if (Wine::counter != 0) {
            cout << "你的对象没有正确释放!\n";
        }
    }
} _c;


int main() {
    int n, m;
    vector<dpair> wines;
    vector<int> qs;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        int d, p;
        scanf("%d%d", &d, &p);
        wines.push_back(dpair(d, p));
    }
    // 按照浓度排序
    sort(wines.begin(), wines.end());

    Wine* d = nullptr; // 链表头节点
    for (int i = 0; i < n; ++i) {
        auto q = new Wine;
        q->d = wines[i].first;
        q->p = wines[i].second;
        while (d != nullptr && d->last != nullptr) {
            if (q->d == d->d) {
                if (q->p < d->p) {
                    d->p = q->p;
                }
                break;
            }
            // 若在最后两点连线下方, 则替换掉最后一个点
            if ((q->p - d->p) / (q->d - d->d) <=
                    (d->p - d->last->p) / (d->d - d->last->d)) {
                Wine* lst = d->last;
                delete d;
                d = lst;
            } else {
                break;
            }
        }

        if (!d || q->d != d->d) {
            q->last = d;
            d = q;
        } else {
            delete q;
        }
    }

    // 将链表转换回数组以便二分查找
    wines.clear();
    for (auto i = d; i; ) {
        wines.push_back(dpair(i->d, i->p));
        Wine* lst = i->last;
        delete i;
        i = lst;
    }
    reverse(wines.begin(), wines.end());

    for (int i = 0; i < m; ++i) {
        int q;
        scanf("%d", &q);
        if (q < wines.front().first || q > wines.back().first) {
            puts("-1");
        } else if (q == wines.front().first) {
            printf("%d.00\n", wines.front().second);
        } else if (q == wines.back().first) {
            printf("%d.00\n", wines.back().second);
        } else {
            // 二分查找 q 所在的线段
            auto it = lower_bound(wines.begin(), wines.end(), dpair(q, 0));
            auto ib = it - 1;
            double res = (it->first - q) / (double)(it->first - ib->first) * ib->second;
            res += (q - ib->first) / (double)(it->first - ib->first) * it->second;
            printf("%.2lf\n", res);
        }
    }
    return 0;
}
```

我和 AI 之间的对话如下：[对话链接](https://kimi.moonshot.cn/share/crqlbvg7061s7gkpi6d0)

## 银行账户异常处理

题目要求通过补全宏定义，以实现一个简单的银行账户系统，可以处理存款和取款操作，并在出现异常时输出相应的错误信息。

我仍然直接将题目文字复制粘贴到 [Kimi.ai - 帮你看更大的世界](https://kimi.moonshot.cn/) 的对话框中。AI 写的代码如下：

```cpp
// 填空定义
#define FILL_1 InvalidInitialDepositException
#define FILL_2 amount < 0
#define FILL_3 balance < amount
#define FILL_4 InsufficientFundsException()
#define FILL_5 InvalidInitialDepositException
```

虽然我已经惊讶于它能够回答出五空中的四空，但 `FILL_1` 的答案是不正确的，此份代码无法通过编译。我尝试这引导 AI 检查 `FILL_1` 是否出现语法错误，它正确地给出了答案：

```cpp
// 填空定义
#define FILL_1 InvalidInitialDepositException()
#define FILL_2 amount < 0
#define FILL_3 balance < amount
#define FILL_4 InsufficientFundsException()
#define FILL_5 InvalidInitialDepositException
```

我和 AI 之间的对话如下：[对话链接](https://kimi.moonshot.cn/share/crql3fi34pecn4nuasug)
