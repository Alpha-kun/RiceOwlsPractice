#include <bits/stdc++.h>
using namespace std;
int tree[500001], q, a;
inline int lowbit(int x) {return x & (-x);}
int query(int pos) {
    int res = 0;
    for (;pos > 0; pos -= lowbit(pos)) {
        res = max(res, tree[pos]);
    }
    return res;
}
void update(int pos, int val) {
    for (;pos <= q; pos += lowbit(pos)) {
        tree[pos] = max(tree[pos], val);
    }
}
int main() {
    scanf("%d", &q);
    int res = 0;
    for (int i = 0; i < q; ++ i) {
        scanf("%d", &a);
        int temp = query(a - 1) + 1;
        // cout << i << " " << a << " " << temp << endl;
        update(a, temp);
        res = max(res, temp);
    }
    printf("%d\n", res);
    return 0;
}
