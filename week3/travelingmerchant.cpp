#include <bits/stdc++.h>

#define INF 2000000005
#define LEN 320
using namespace std;

int n;

int B;
int L[LEN], R[LEN];

struct sequence {
    int p[100005] = {0};

    int MAX[LEN], MIN[LEN], OPTLR[LEN], OPTRL[LEN];

    void preprocess() {
        for (int i = 0; i <= B; ++i) {
            int mx = -1, mn = INF, opt = -1;
            for (int j = L[i]; j <= R[i]; ++j) {
                opt = max(opt, p[j] - mn);
                mx = max(mx, p[j]);
                mn = min(mn, p[j]);
            }
            MAX[i] = mx, MIN[i] = mn, OPTLR[i] = opt;

            mn = INF, opt = -1;
            for (int j = R[i]; j >= L[i]; --j) {
                opt = max(opt, p[j] - mn);
                mn = min(mn, p[j]);
            }
            OPTRL[i] = opt;
        }
    }

    int queryLR(int l, int r) {
        int mn = INF, opt = -1;
        int B1 = l / LEN, B2 = r / LEN;
        if (B1 == B2) {
            for (int i = l; i <= r; ++i) {
                opt = max(opt, p[i] - mn);
                mn = min(mn, p[i]);
            }
            return opt;
        }
        for (int i = l; i <= R[B1]; ++i) {
            opt = max(opt, p[i] - mn);
            mn = min(mn, p[i]);
        }
        for (int i = B1 + 1; i < B2; ++i) {
            opt = max(opt, MAX[i] - mn);
            opt = max(opt, OPTLR[i]);
            mn = min(mn, MIN[i]);
        }
        for (int i = L[B2]; i <= r; ++i) {
            opt = max(opt, p[i] - mn);
            mn = min(mn, p[i]);
        }
        return opt;
    }

    int queryRL(int r, int l) {
        int mn = INF, opt = -1;
        int B1 = r / LEN, B2 = l / LEN;
        if (B1 == B2) {
            for (int i = r; i >= l; --i) {
                opt = max(opt, p[i] - mn);
                mn = min(mn, p[i]);
            }
            return opt;
        }
        for (int i = r; i >= L[B1]; --i) {
            opt = max(opt, p[i] - mn);
            mn = min(mn, p[i]);
        }
        for (int i = B1 - 1; i > B2; --i) {
            opt = max(opt, MAX[i] - mn);
            opt = max(opt, OPTRL[i]);
            mn = min(mn, MIN[i]);
        }
        for (int i = R[B2]; i >= l; --i) {
            opt = max(opt, p[i] - mn);
            mn = min(mn, p[i]);
        }
        return opt;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    B = n / LEN;
    for (int i = 0; i <= B; ++i) {
        L[i] = max(1, i * LEN);
        R[i] = min((i + 1) * LEN - 1, n);
        if (R[i] == n) break;
    }

    int v[n + 1], d[n + 1];
    for (int i = 1; i <= n; ++i) {
        cin >> v[i] >> d[i];
    }

    int mult[7] = {0, 1, 2, 3, 2, 1, 0};
    sequence price[7];
    for (int i = 0; i < 7; ++i) {
        for (int j = 1; j <= n; ++j) {
            price[i].p[j] = v[j] + mult[(i + j - 1) % 7] * d[j];
        }
        price[i].preprocess();
    }

    int q, s, t;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> s >> t;
        if (s < t) {
            printf("%d\n", max(price[(7 - ((s - 1) % 7)) % 7].queryLR(s, t), 0));
        } else {
            printf("%d\n", max(price[(6 - ((s - 1) % 7))].queryRL(s, t), 0));
        }
    }
    return 0;
}
