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
