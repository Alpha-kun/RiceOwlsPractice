#include <bits/stdc++.h>

using namespace std;

typedef long long ll;


int d;

void testcase() {
    vector<double> rate(d + 1);
    for (int i = 1; i <= d; ++i) {
        cin >> rate[i];
    }
    ll dp[d + 1][2];
    dp[0][0] = 0;
    dp[0][1] = 100000;
    for (int i = 1; i <= d; ++i) {
        dp[i][0] = max(dp[i - 1][0], ((ll) floor((0.97 * dp[i - 1][1] / rate[i]))));
        dp[i][1] = max(dp[i - 1][1], ((ll) floor((0.97 * dp[i - 1][0] * rate[i]))));
    }
    printf("%.2f\n", dp[d][1] / 100.0);
}

int main() {
    while (cin >> d) {
        if (d == 0) break;
        testcase();
    }
    return 0;
}
