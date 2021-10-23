#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll h;
    int w;
    cin >> h >> w;
    ll b[w];
    ll land = 0;
    for (int i = 0; i < w; ++i) {
        cin >> b[i];
        land += b[i];
    }

    ll lo = 0, hi = h, mid;
    while (lo + 1 < hi) {
        mid = (lo + hi) >> 1;
        ll water = 0;
        for (int i = 0; i < w; ++i) {
            water += max(0ll, mid - b[i]);
        }
        ll air = h * w - water - land;
        if (water - air >= 0) hi = mid;
        else lo = mid;
    }

//    cout << lo << ',' << hi << endl;

    ll waterlo = 0;
    for (int i = 0; i < w; ++i) {
        waterlo += max(0ll, lo - b[i]);
    }
    ll airlo = h * w - waterlo - land;
    ll difflo = abs(waterlo - airlo);

    ll waterhi = 0;
    for (int i = 0; i < w; ++i) {
        waterhi += max(0ll, hi - b[i]);
    }
    ll airhi = h * w - waterhi - land;
    ll diffhi = abs(waterhi - airhi);

    ll opt = min(difflo, diffhi);
    hi = difflo == opt ? lo : hi;
    lo = 0;
    while (lo + 1 < hi) {
        mid = (lo + hi) >> 1;
        ll water = 0;
        for (int i = 0; i < w; ++i) {
            water += max(0ll, mid - b[i]);
        }
        ll air = h * w - water - land;
        if (abs(water - air) >= opt) lo = mid;
        else hi = mid;
    }

    waterlo = 0;
    for (int i = 0; i < w; ++i) {
        waterlo += max(0ll, lo - b[i]);
    }
    airlo = h * w - waterlo - land;
    difflo = abs(waterlo - airlo);

    waterhi = 0;
    for (int i = 0; i < w; ++i) {
        waterhi += max(0ll, hi - b[i]);
    }
    airhi = h * w - waterhi - land;
    diffhi = abs(waterhi - airhi);

    if (difflo == opt) cout << lo << ' ' << waterlo << endl;
    else cout << hi << ' ' << waterhi << endl;
    return 0;
}
