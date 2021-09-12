#include <bits/stdc++.h>

using namespace std;

int n;

vector<int> pre, post;

bool boring(int l, int r) {
    if (r <= l) return false;
    for (int d = 0; l + d <= r - d; ++d) {
        if (pre[l + d] < l && r < post[l + d])
            return boring(l, l + d - 1) | boring(l + d + 1, r);
        if (pre[r - d] < l && r < post[r - d])
            return boring(l, r - d - 1) | boring(r - d + 1, r);
    }
    return true;
}

void testcase() {
    cin >> n;
    pre = vector<int>(n), post = vector<int>(n, n);
    map<int, int> pos;
    int x;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        if (pos.find(x) != pos.end()) {
            pre[i] = pos[x];
        } else {
            pre[i] = -1;
        }
        pos[x] = i;
    }
    for (int i = 0; i < n; ++i) {
        if (pre[i] != -1) post[pre[i]] = i;
    }

    if (boring(0, n - 1)) printf("boring\n");
    else printf("non-boring\n");
}

int main() {
    int t;
    cin >> t;
    while (t-- > 0) {
        testcase();
    }
    return 0;
}
