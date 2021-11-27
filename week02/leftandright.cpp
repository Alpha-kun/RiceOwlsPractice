#include <bits/stdc++.h>

using namespace std;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    string S;
    cin >> n >> S;

    int i = 0;
    if (S[0] == 'R') {
        cout << "1\n";
    } else {
        int j = 0;
        while (j + 1 < n - 1 && S[j + 1] == 'L') {
            j++;
        };
        for (int k = j + 1; k >= 0; --k) {
            cout << k + 1 << endl;
        }
        i = j + 1;
    }
    while (i < n - 1) {
        int j = i;
        while (j + 1 < n - 1 && S[j + 1] == 'L') {
            j++;
        }
        cout << j + 2 << endl;
        for (int k = 0; k < j - i; ++k) {
            cout << j + 1 - k << endl;
        }
        i = j + 1;
    }
    return 0;
}
