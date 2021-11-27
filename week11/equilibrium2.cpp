#include <iostream>
#include <vector>

using namespace std;

const int maxn = 1e5 + 7;
vector<int> vec[maxn];
vector<int> ans;
void dfs(int lst, int cur, int lft) {
    int cnt = lft;
    int _lft = 0;
    if (vec[cur].size() / 2 <= lft) {
        // cout << cur << endl;
        ans.push_back(cur);
        _lft = 1;
    }
    for (int i = 0; i < vec[cur].size(); ++ i) {
        if (vec[cur][i] == lst) continue;
        dfs(cur, vec[cur][i], _lft);
        cnt ++;
        // cout << cur << " " << cnt << endl;
        if (cnt == vec[cur].size() / 2) {
            // cout << cur << endl;
            ans.push_back(cur);
            _lft = 1;
        }
    }

}
int main() {
    int n, u, v;
    scanf("%d", &n);
    for (int i = 1; i < n; ++ i) {
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    dfs(-1, 0, 0);
    for (int i = 0; i < n; ++ i) {
        printf("%d%c", ans[i], " \n"[i == n - 1]);
    }
    return 0;
}
