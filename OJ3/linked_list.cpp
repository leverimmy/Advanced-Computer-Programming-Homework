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
