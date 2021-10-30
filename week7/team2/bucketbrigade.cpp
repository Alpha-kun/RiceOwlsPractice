#include <bits/stdc++.h>
using namespace std;
int main() {
    double n, v, x, f, t;
    while (cin >> n >> v >> x >> f >> t) {
        double p = v / ceil(v / x);
        cout << fixed << setprecision(10) << (n - 1) * (t + p / f) + 2 * v / f + (2 * ceil(v / x) - 1) * t << endl;
    }
    return 0;
}
