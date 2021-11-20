#include <bits/stdc++.h>

using namespace std;

int lg(int x) {
    return x == 1 ? 0 : (1 + lg(x >> 1));
}

double dp[1 << 20];

int main() {
    double rx, ry;
    cin >> rx >> ry;
    int n;
    cin >> n;
    double x[20], y[20];
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }
    for (int S = 1; S < 1 << n; ++S) {
        int mask = S;
        int lo = mask & -mask;
        int i = lg(lo);
        mask -= lo;
        dp[S] = numeric_limits<double>::infinity();
        if (__builtin_popcount(S) == 1) {
            dp[S] = hypot(rx - x[i], ry - y[i]);
        } else if (__builtin_popcount(S) == 2) {
            lo = mask & -mask;
            int j = lg(lo);
            dp[S] = hypot(x[j] - x[i], y[j] - y[i]) + min(hypot(rx - x[i], ry - y[i]), hypot(rx - x[j], ry - y[j]));
        } else {
#if 0
            dp[S] = dp[S - (1 << i)] + 2 * hypot(rx - x[i], ry - y[i]);
            while (mask != 0) {
                lo = mask & -mask;
                int j = lg(lo);
                mask -= lo;
                dp[S] = min(dp[S], dp[S - (1 << i) - (1 << j)] + hypot(x[j] - x[i], y[j] - y[i]) +
                                   hypot(rx - x[i], ry - y[i]) +
                                   hypot(rx - x[j], ry - y[j]));
            }
#endif
			for (int j=0; j<n; ++j) {
				if (S & (1<<j)) {
					dp[S] = min(dp[S], dp[S - (1<<j)] + 2*hypot(rx - x[j], ry - y[j]));
					for (int k=0; k<j; ++k) {
						if (S & (1<<k)) {
							dp[S] = min(dp[S], dp[S - (1<<j) - (1<<k)] + hypot(x[k]-x[j], y[k]-y[j]) + hypot(rx - x[j], ry - y[j]) + hypot(rx - x[k], ry - y[k]));
						}
					}
				}
			}
        }
    }
    cout << setprecision(17) << dp[(1 << n) - 1] << endl;
    return 0;
}