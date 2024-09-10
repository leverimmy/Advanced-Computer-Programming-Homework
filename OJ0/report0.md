# OJ0

## A+B Problem

这题的解题思路较为简单，按照题目内容输入两个 `int` 类型的整型数之后输出两数之和即可。

我直接将题目文字复制粘贴到 [Kimi.ai - 帮你看更大的世界](https://kimi.moonshot.cn/) 的对话框中，要求其提供一个 C++ 代码解决此问题。AI 写的代码如下：

```cpp
#include <iostream>

int main() {
    int a, b;
    std::cin >> a >> b; // 读取两个整数
    std::cout << a + b << std::endl; // 输出它们的和
    return 0;
}
```

AI 写的代码十分直观，直接按照题目所描述的要求进行操作。同时，AI 还在代码中添加了注释，这样可以方便我们进行阅读。此代码成功通过了本题。

我和 AI 之间的对话如下：[对话链接](https://kimi.moonshot.cn/share/crfotfg04rjaohvet3p0)

## C6-2 数组第K小数

题目要求给出一个数组的第 $k$ 小的数字。这题的解题思路是，将数组从小到大排序，最后输出第 $k$ 位元素即可。

我仍然直接将题目文字复制粘贴到 [Kimi.ai - 帮你看更大的世界](https://kimi.moonshot.cn/) 的对话框中，要求其提供一个 C++ 代码解决此问题。AI 写的代码如下：

```cpp
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
```

AI 通过详细的注释解释了每一行代码的作用以及意义。它的思路和我一样，将数组从小到大排序，这样第 $k$ 小的数就排在排序后数组的第 $k$ 位，输出下标为 $k$ 的数即可。此代码成功通过了本题。

我和 AI 之间的对话如下：[对话链接](https://kimi.moonshot.cn/share/crfp376cp7f84ga5so7g)

## 多项式运算库

题目要求实现多项式加法和乘法。解题思路是按照竖式加法和乘法进行运算即可。

我仍然直接将题目文字复制粘贴到 [Kimi.ai - 帮你看更大的世界](https://kimi.moonshot.cn/) 的对话框中，要求其提供一个 C++ 代码解决此问题。AI 写的代码如下：

```cpp
#include "poly.h"
#include <vector>

std::vector<int> poly_plus(const std::vector<int> &poly0, const std::vector<int> &poly1) {
    std::vector<int> res(std::max(poly0.size(), poly1.size()), 0);
    for (size_t i = 0; i < poly0.size(); ++i) {
        res[i] += poly0[i];
    }
    for (size_t i = 0; i < poly1.size(); ++i) {
        res[i] += poly1[i];
    }
    return res;
}

std::vector<int> poly_mul(const std::vector<int> &poly0, const std::vector<int> &poly1) {
    std::vector<int> res(poly0.size() + poly1.size() - 1, 0);
    for (size_t i = 0; i < poly0.size(); ++i) {
        for (size_t j = 0; j < poly1.size(); ++j) {
            res[i + j] += poly0[i] * poly1[j];
        }
    }
    return res;
}
```

AI 编写的代码简洁明了，通过补全 `poly_plus` 和 `poly_mul` 来实现多项式的加法和乘法。此代码成功通过了本题。

- 在加法函数中，创建一个与输入多项式长度相同的结果向量，然后分别将两个多项式的系数相加。
- 在乘法函数中，创建一个长度为两个多项式长度之和减一的结果向量，然后通过嵌套循环计算乘积。

我和 AI 之间的对话如下：[对话链接](https://kimi.moonshot.cn/share/crfp3g6bi7seqsaqu8gg)

## AVL

解题思路有很多，使用传统的平衡树，实现插入、删除、查找第 $k$ 大元素和查询某数 $x$ 的排名，理应即可通过此题。

我仍然直接将题目文字复制粘贴到 [Kimi.ai - 帮你看更大的世界](https://kimi.moonshot.cn/) 的对话框中，要求其提供一个 C++ 代码解决此问题。AI 写的代码如下：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    TreeNode* root;
    int count;

public:
    Solution() : root(nullptr), count(0) {}

    // 插入操作
    void insert(int x) {
        root = insert(root, x);
    }

    // 删除操作
    void erase(int k) {
        count--;
        root = erase(root, k);
    }

    // 查询操作
    int query() {
        int greater = 0;
        TreeNode* node = root;
        while (node) {
            if (node->val > root->val) {
                greater++;
                node = node->right;
            } else {
                node = node->left;
            }
        }
        return greater;
    }

    // 辅助函数：插入
    TreeNode* insert(TreeNode* node, int x) {
        if (!node) {
            count++;
            return new TreeNode(x);
        }
        if (x < node->val) {
            node->left = insert(node->left, x);
        } else if (x > node->val) {
            node->right = insert(node->right, x);
        }
        return node;
    }

    // 辅助函数：删除
    TreeNode* erase(TreeNode* node, int k) {
        if (!node) return node;
        if (k == 1) {
            TreeNode* temp = node->left ? eraseMin(node->left) : node->right;
            delete node;
            return temp;
        } else if (k < count / 2) {
            node->left = erase(node->left, k);
        } else {
            node->right = erase(node->right, k - count / 2 - 1);
        }
        return node;
    }

    // 辅助函数：找到并删除最小值
    TreeNode* eraseMin(TreeNode* node) {
        if (!node->left) {
            TreeNode* rightNode = node->right;
            delete node;
            return rightNode;
        }
        node->left = eraseMin(node->left);
        return node;
    }
};

int main() {
    int m;
    cin >> m;
    Solution solution;
    for (int i = 0; i < m; ++i) {
        int op, x, k;
        cin >> op;
        if (op == 1) {
            cin >> x;
            solution.insert(x);
            cout << solution.query() << endl;
        } else if (op == 2) {
            cin >> k;
            cout << solution.erase(k) << endl;
        }
    }
    return 0;
}
```

但是此代码无法通过编译。所以我想到了能够使用 01Trie 这种数据结构实现这些功能。由于 $1 \le x \le 10^9$，所以 $x$ 作为一个 `int` 类型的数据最多只会有 $31$ 位。可以使用一个字符集仅为 $\{0, 1\}$，深度为 $31$ 的 Trie 树来存储每一个数。统计每个节点的子树大小即可实现查找第 $k$ 大、查询某数 $x$ 的排名的操作。我写的代码如下：

```cpp
#include <bits/stdc++.h>

const int N = 3.2e7 + 5;

class Trie {
private:
    int cnt, ch[N][2], siz[N];
public:
    void insert(int val) {
        int cur = 1;
        for (int i = 30; i >= 0; i--) {
            int b = (val >> i) & 1;
            if (!ch[cur][b]) {
                ch[cur][b] = ++cnt;
            }
            siz[cur]++;
            cur = ch[cur][b];
        }
        siz[cur]++;
    }
    void remove(int val) {
        int cur = 1;
        for (int i = 30; i >= 0; i--) {
            int b = (val >> i) & 1;
            siz[cur]--;
            cur = ch[cur][b];
        }
        siz[cur]--;
    }
    int size() {
        return siz[1];
    }
    int kth(int k) {
        int cur = 1, res = 0;
        while (ch[cur][0] || ch[cur][1]) {
            if (siz[ch[cur][0]] >= k) {
                cur = ch[cur][0];
                res <<= 1;
            } else {
                k -= siz[ch[cur][0]];
                cur = ch[cur][1];
                res = res << 1 | 1;
            }
        }
        return res;
    }
    int rank(int val) {
        int cur = 1, res = 0;
        for (int i = 30; i >= 0; i--) {
            int b = (val >> i) & 1;
            if (b) {
                res += siz[ch[cur][0]];
            }
            cur = ch[cur][b];
        }
        return res + siz[cur];
    }

    Trie() {
        cnt = 1;
    }
} candy_bag;

int main() {
    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; ++i) {
        int op, x, k;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d", &x);
            candy_bag.insert(x);
            printf("%d\n", candy_bag.size() - candy_bag.rank(x));
        } else if (op == 2) {
            scanf("%d", &k);
            x = candy_bag.kth(candy_bag.size() - k + 1);
            printf("%d\n", x);
            candy_bag.remove(x);
        }
    }
    return 0;
}
```

AI 能够理解我的代码，此代码成功通过了本题。

> 你的代码已经很完整，并且正确地实现了题目要求的功能。它使用了 01 Trie 树来高效地处理数字的插入、删除和查询操作。这种数据结构特别适合处理大量数字的排名和查找问题，因为它可以快速地在数字的二进制表示上进行操作。

我和 AI 之间的对话如下：[对话链接](https://kimi.moonshot.cn/share/crfpafkubms1v70lue80)