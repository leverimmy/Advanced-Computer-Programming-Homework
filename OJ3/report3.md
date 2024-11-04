# OJ3

## Linked List

### 解题思路

维护一个双向链表，使用两个数组 `pre[]` 和 `nxt[]` 分别记录每个节点的前驱和后继。
在每次操作时，根据操作类型进行相应的操作即可。

- 如果是 `1`，则将 `x` 移动到 `y` 的后面。此时需要注意，如果 `y` 已经是 `x` 的后继，则不需要进行操作。
  - 首先找到 `x` 的前驱 `px`，后继 `nx`，`y` 的后继 `ny`。
    - 将 `px` 的后继指向 `nx`，`nx` 的前驱指向 `px`。
    - 将 `y` 的后继指向 `x`，`x` 的前驱指向 `y`。
    - 将 `x` 的后继指向 `ny`，`ny` 的前驱指向 `x`。
- 如果是 `2`，则按照从头到尾的顺序输出链表中的元素。

### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, m, pre[N], nxt[N];

int main() {
    scanf("%d %d", &n, &m);

    nxt[0] = 1;
    for (int i = 1; i <= n; i++) {
        pre[i] = i - 1;
        nxt[i] = i + 1;
    }
    pre[n + 1] = n;

    for (int i = 1; i <= m; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int x, y;
            scanf("%d %d", &x, &y);
            
            int px = pre[x], nx = nxt[x], ny = nxt[y];

            if (ny == x) {
                continue;
            }
            nxt[px] = nx;
            pre[nx] = px;
            nxt[y] = x;
            pre[x] = y;
            nxt[x] = ny;
            pre[ny] = x;
        } else if (op == 2) {
            for (int j = nxt[0]; j != n + 1; j = nxt[j]) {
                printf("%d ", j);
            }
            printf("\n");
        }
    }
    return 0;
}
```

## GEMM

### 解题思路

直接使用 `Eigen` 库中的 `MatrixXd` 类型即可。注意，`Eigen` 库中的 `MatrixXd` 类型是从 `0` 开始编号的，因此在输入输出时需要注意。
同时，`MatrixXd` 类型中的元素是 `double` 类型，因此在输出时需要进行强制类型转换。

### 代码实现

```cpp
#include <bits/stdc++.h>
#include <Eigen/Dense>
using namespace std;

int n, m, p, q;

int main() {
    cin >> n >> m >> p >> q;

    Eigen::MatrixXd matA(n, m), matB(p, q), matC(n, q);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matA(i, j);
        }
    }
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < q; j++) {
            cin >> matB(i, j);
        }
    }

    matC = matA * matB;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < q; j++) {
            cout << (int)matC(i, j) << " ";
        }
        cout << endl;
    }
    return 0;
}
```

## 反馈与建议

这次作业较为简单，没有遇到太大的问题。我没有使用 AI 的辅助就完成了本次作业。在实现链表时，我认为画图是一个很好的方法，可以帮助理清思路。
