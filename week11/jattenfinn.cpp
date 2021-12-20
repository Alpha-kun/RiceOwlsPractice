#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int opt = 0, pid = -1;
    int r = -1;
    for (int i = 0; i < n; ++i) {
        if (r >= i) continue;
        int lp = i - 1, rp = i + 1;
        while (true) {
            if (0 <= lp && (rp - lp) * 500 + 500 > a[lp]) lp--;
            else if (rp < n && (rp - lp) * 500 + 500 > a[rp]) rp++;
            else break;
        }
        r = max(r, rp - 1);
        if (rp - lp - 1 > opt) {
            opt = rp - lp - 1;
            pid = i;
        }
    }
    cout << opt << " " << pid << endl;
    return 0;
}
