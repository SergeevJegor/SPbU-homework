#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0;
    cin >> n;

    int adj;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> adj;
            if (j > i) {
                if (adj) {
                    cout << i + 1 << ' ' << j + 1 << '\n';
                }
            }
        }
    }

    return 0;
}
