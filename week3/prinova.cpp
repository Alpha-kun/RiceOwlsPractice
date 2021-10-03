#include <bits/stdc++.h>

using namespace std;


int main() {
    int n, a, b;
    cin >> n;
    vector<int> boy(n);
    for (int i = 0; i < n; ++i) {
        cin >> boy[i];
    }
    sort(boy.begin(), boy.end());
    cin >> a >> b;
    a += (a % 2 ? 0 : 1);
    b -= (b % 2 ? 0 : 1);


    int opt = -1, ov = -1;

    int adist = 1000000001;
    for (int i = 0; i < n; ++i) {
        adist = min(adist, abs(a - boy[i]));
    }
    if (adist > ov) {
        ov = adist;
        opt = a;
    }

    int bdist = 1000000001;
    for (int i = 0; i < n; ++i) {
        bdist = min(bdist, abs(b - boy[i]));
    }
    if (bdist > ov) {
        ov = bdist;
        opt = b;
    }

    for (int i = 0; i < n - 1; ++i) {
        int name = (boy[i] + boy[i + 1]) >> 1;
        if (name % 2 == 0) name++;
        if (a <= name && name <= b) {
            if (min(abs(name - boy[i]), abs(name - boy[i + 1])) > ov) {
                opt = name;
                ov = min(abs(name - boy[i]), abs(name - boy[i + 1]));
            }
        }
    }

    cout << opt << endl;
    return 0;
}
