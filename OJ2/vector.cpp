#include <bits/stdc++.h>
using namespace std;

int main() {
    int a[10];
    for (int i = 0; i < 10; i++) {
        cin >> a[i];
    }

    vector<int> vec = vector<int>(a, a + 10);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int operation_id;
        cin >> operation_id;
        if (operation_id == 1) {
            int value;
            cin >> value;
            vec.push_back(value);
        } else if (operation_id == 2) {
            if (!vec.empty())
                vec.pop_back();
        } else if (operation_id == 3) {
            int position, value;
            cin >> position >> value;
            if (position >= 0 && position <= vec.size()) {
                vec.insert(vec.begin() + position, value);
            }
        } else if (operation_id == 4) {
            int position;
            cin >> position;
            if (position >= 0 && position < vec.size()) {
                vec.erase(vec.begin() + position);
            }
        } else if (operation_id == 5) {
            cout << vec.size() << endl;
        } else if (operation_id == 6) {
            for (auto it = vec.begin(); it != vec.end(); it++) {
                cout << *it << " ";
            }
            cout << endl;
        } else if (operation_id == 7) {
            for (auto it = vec.rbegin(); it != vec.rend(); it++) {
                cout << *it << " ";
            }
            cout << endl;
        } else if (operation_id == 8) {
            int position;
            cin >> position;
            if (position >= 0 && position < vec.size()) {
                cout << vec[position] << endl;
            } else {
                cout << "Invalid position" << endl;
            }
        }
    }
    return 0;
}
