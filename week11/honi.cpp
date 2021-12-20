#include <bits/stdc++.h>

#define MOD 1000000007
using namespace std;
typedef long long ll;

int main() {
    int n;
    cin >> n;

    ll a[n], b[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        cin >> b[i];
    }
    b[n - 1] = 0ll;

    ll dp[n][3];
    dp[0][0] = a[0] + b[0] % MOD;
    dp[0][1] = a[0] + b[0] % MOD;
    dp[0][2] = a[0] + max(b[0] - 1, 0ll) % MOD;

    for (int i = 1; i < n; ++i) {
        dp[i][0] = dp[i - 1][0] * a[i] % MOD;//0
        dp[i][0] += dp[i - 1][1] * b[i] % MOD;//1
        dp[i][0] += dp[i - 1][2] * b[i - 1] % MOD;//2
        dp[i][0] %= MOD;

        dp[i][1] = dp[i - 1][0] * a[i] % MOD;//0
        dp[i][1] += dp[i - 1][1] * b[i] % MOD;//1
        dp[i][1] += dp[i - 1][2] * b[i - 1] % MOD;//2
        dp[i][1] %= MOD;

        dp[i][2] = dp[i - 1][0] * a[i] % MOD;//0
        dp[i][2] += dp[i - 1][1] * max(b[i] - 1, 0ll) % MOD;//1
        dp[i][2] += dp[i - 1][2] * b[i - 1] % MOD;//2
        dp[i][2] %= MOD;
    }

    cout << dp[n - 1][0] << endl;

    return 0;
}
