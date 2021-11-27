#include <iostream>
#include <cstring>

using namespace std;

const int maxn = 1e3 + 5;
int _x[maxn], _y[maxn], _z[maxn];
int x, y, z, u, v, w, cnt[maxn], xx[maxn][2], yy[maxn][2], zz[maxn][2];

int main() {
    int a, b, c, m;
    while(scanf("%d", &a) != EOF) {
        if (a == -1) break;
        else {
            scanf("%d%d%d", &b, &c, &m);
        }
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < m; ++ i) {
            scanf("%d%d%d", &_x[i], &_y[i], &_z[i]);
        }
        bool flag = true;
        long long sum = 0;
        for (int i = 0; i < m; ++ i) {
            scanf("%d%d%d%d%d%d", &x, &y, &z, &u, &v, &w);
            if (x > u || y > v || z > w) {
                flag = false;
            }
            xx[i][0] = min(x, u), xx[i][1] = max(x, u);
            yy[i][0] = min(y, v), yy[i][1] = max(y, v);
            zz[i][0] = min(z, w), zz[i][1] = max(z, w);
            sum += 1ll * (xx[i][1] - xx[i][0] + 1) * (yy[i][1] - yy[i][0] + 1) * (zz[i][1] - zz[i][0] + 1);
            if (xx[i][1] > a || yy[i][1] > b || zz[i][1] > c) {
                flag = false;
            }
            if (xx[i][0] <= _x[i] && _x[i] <= xx[i][1]
                && yy[i][0] <= _y[i] && _y[i] <= yy[i][1]
                && zz[i][0] <= _z[i] && _z[i] <= zz[i][1]) {
                ++ cnt[i];
            }
            if (cnt[i] != 1) {
                flag = false;
            }
        }
        if (sum != 1ll * a * b * c) {
            flag = false;
        }
        for (int i = 0; flag && i < m; ++ i) {
            for (int j = 0; flag && j < m; ++ j) {
                if (i == j) continue;
                for (int bit = 0; flag && bit < (1 << 3); ++ bit) {
                    int _xx = xx[j][(bit >> 2) & 1];
                    int _yy = yy[j][(bit >> 1) & 1];
                    int _zz = zz[j][(bit >> 0) & 1];
                    if (xx[i][0] <= _xx && _xx <= xx[i][1]
                        && yy[i][0] <= _yy && _yy <= yy[i][1]
                        && zz[i][0] <= _zz && _zz <= zz[i][1]) {
                        flag = false;
                    }
                }
            }
        }
        puts(flag ? "YES" : "NO");
    }
    return 0;
}
