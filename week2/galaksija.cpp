#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int p[100005];
vector<pii> G[100005];
int sz[100005];
int f[100005] = {0};
map<int, int> cont[100005];

int root(int i) {
    return p[i] == i ? i : root(p[i]);
}

vector<ll> ans(1, 0ll);

void dfs1(int u, int pnt, int z, int rtv) {
    f[u] = z;
    ans[ans.size() - 1] += cont[rtv][z];
    for (pii e: G[u]) {
        if (e.first != pnt) {
            dfs1(e.first, u, z ^ e.second, rtv);
        }
    }
}

void dfs2(int u, int pnt, int rtv) {
    cont[rtv][f[u]]++;
    for (pii e: G[u]) {
        if (e.first != pnt) {
            dfs2(e.first, u, rtv);
        }
    }
}

void uni(int u, int v, int z) {
    if (sz[root(u)] > sz[root(v)]) swap(u, v);

    ans.push_back(ans.back());

    dfs1(u, v, z ^ f[v], root(v));
    dfs2(u, v, root(v));

    G[u].push_back(make_pair(v, z));
    G[v].push_back(make_pair(u, z));

    sz[root(v)] += sz[root(u)];
    p[root(u)] = root(v);
}


int main() {
    fill_n(sz, 100005, 1);
    iota(p, p + 100005, 0);

    int n;
    cin >> n;
    int a[n], b[n], z[n];
    for (int i = 1; i <= n - 1; ++i) {
        cin >> a[i] >> b[i] >> z[i];
    }

    for (int i = 1; i <= n; ++i) {
        cont[i][0] = 1;
    }

    vector<int> order(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> order[i];
    }

    for (int i = n - 2; i >= 0; --i) {
        uni(a[order[i]], b[order[i]], z[order[i]]);
    }

    for (int i = n - 1; i >= 0; --i) {
        cout << ans[i] << endl;
    }
    return 0;
}
