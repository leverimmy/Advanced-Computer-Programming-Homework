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