#include <bits/stdc++.h>

using namespace std;

vector<string> slb;

int dp[100][8];

string str;

int f(int i, int s) {
    if (i == str.size()) return s == 0 ? 1 : 0;
    if (s == 0) return 0;
    if (dp[i][s] != -1) return dp[i][s];
    if (str[i] == ' ') return f(i + 1, s);

    dp[i][s] = 0;
    for (string ptn: slb) {
        if (i + ptn.size() > str.size()) {
            continue;
        }
        bool flag = true;
        for (int j = 0; j < ptn.size(); ++j) {
            if (str[i + j] != ptn[j]) {
                flag = false;
                break;
            }
        }
        if (!flag) continue;
        dp[i][s] |= f(i + ptn.size(), s - 1);
    }
    return dp[i][s];
}

int main() {
    int S;
    string line;
    getline(cin, line);
    S = stoi(line);
    for (int i = 0; i < S; ++i) {
        getline(cin, line);
        slb.push_back(line);
    }

    getline(cin, str);
    memset(dp, -1, sizeof(dp));
    bool h1 = f(0, 5);

    getline(cin, str);
    memset(dp, -1, sizeof(dp));
    bool h2 = f(0, 7);

    getline(cin, str);
    memset(dp, -1, sizeof(dp));
    bool h3 = f(0, 5);

//    cout << h1 << ' ' << h2 << ' ' << h3 << endl;
    if (h1 && h2 && h3) {
        cout << "haiku" << endl;
    } else {
        cout << "come back next year" << endl;
    }
    return 0;
}
