#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll a, b;

ll roaddist(ll x1, ll y1, ll x2, ll y2) {
    if (x1 % a == 0) {
        if (x2 == x1) return abs(y1 - y2);
        ll cy1 = (y1 / b) * b;
        ll cy2 = (y1 / b + 1) * b;
        return abs(x1 - x2) + min(abs(cy1 - y2) + abs(y1 - cy1), abs(cy2 - y2) + abs(y1 - cy2));
    } else {
        //y1 % b == 0
        if (y2 == y1) return abs(x1 - x2);
        ll cx1 = (x1 / a) * a;
        ll cx2 = (x1 / a + 1) * a;
        return abs(y1 - y2) + min(abs(cx1 - x2) + abs(x1 - cx1), abs(cx2 - x2) + abs(x1 - cx2));
    }
}

vector<ll> xcd, ycd;
ll dis;

void toroad(ll x, ll y) {
    xcd = vector<ll>();
    ycd = vector<ll>();
    if (x % a == 0 || y % b == 0) {
        xcd.push_back(x);
        ycd.push_back(y);
        dis = 0;
        return;
    }
    ll x1 = (x / a) * a;
    ll x2 = (x / a + 1) * a;
    ll y1 = (y / b) * b;
    ll y2 = (y / b + 1) * b;

    ll optdis = min(min(abs(x - x1), abs(x - x2)), min(abs(y - y1), abs(y - y2)));

    if (abs(x - x1) == optdis) {
        xcd.push_back(x1);
        ycd.push_back(y);
    }
    if (abs(x - x2) == optdis) {
        xcd.push_back(x2);
        ycd.push_back(y);
    }
    if (abs(y - y1) == optdis) {
        xcd.push_back(x);
        ycd.push_back(y1);
    }
    if (abs(y - y2) == optdis) {
        xcd.push_back(x);
        ycd.push_back(y2);
    }
    dis = optdis;
}

ll shortest(ll x1, ll y1, ll x2, ll y2) {
    toroad(x1, y1);
    vector<ll> xcand1 = xcd;
    vector<ll> ycand1 = ycd;
    ll dist1 = dis;
//    cout << dist1 << endl;
    toroad(x2, y2);
    vector<ll> xcand2 = xcd;
    vector<ll> ycand2 = ycd;
    ll dist2 = dis;
//    cout << dist2 << endl;
    ll opt = 1000000000000ll;
    for (int i = 0; i < xcand1.size(); ++i) {
        for (int j = 0; j < xcand2.size(); ++j) {
//            cout << xcand1[i] << ' ' << ycand1[i] << ' ' << xcand2[j] << ' ' << ycand2[j] << endl;
//            cout << roaddist(xcand1[i], ycand1[i], xcand2[j], ycand2[j]) << endl;
            opt = min(opt, dist1 + dist2 + roaddist(xcand1[i], ycand1[i], xcand2[j], ycand2[j]));
        }
    }
    return opt;
}

int main() {
    int t;
    cin >> t;
    ll x1, y1, x2, y2;
    for (int i = 0; i < t; ++i) {
        cin >> a >> b >> x1 >> y1 >> x2 >> y2;
        x1 += (100000000 / a + 1) * a;
        x2 += (100000000 / a + 1) * a;
        y1 += (100000000 / b + 1) * b;
        y2 += (100000000 / b + 1) * b;
        cout << shortest(x1, y1, x2, y2) << endl;
    }
    return 0;
}
