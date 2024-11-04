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
