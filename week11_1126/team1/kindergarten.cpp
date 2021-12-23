#include <bits/stdc++.h>

using namespace std;

int n;//=2* # of variables
vector<vector<int>> g, gt;
vector<bool> used;
vector<int> order, comp;
vector<bool> assignment;

void dfs1(int v) {
    used[v] = true;
    for (int u: g[v]) {
        if (!used[u])
            dfs1(u);
    }
    order.push_back(v);
}

void dfs2(int v, int cl) {
    comp[v] = cl;
    for (int u: gt[v]) {
        if (comp[u] == -1)
            dfs2(u, cl);
    }
}

bool solve_2SAT() {
    order.clear();
    used.assign(n, false);
    for (int i = 0; i < n; ++i) {
        if (!used[i])
            dfs1(i);
    }

    comp.assign(n, -1);
    for (int i = 0, j = 0; i < n; ++i) {
        int v = order[n - i - 1];
        if (comp[v] == -1)
            dfs2(v, j++);
    }

    assignment.assign(n / 2, false);
    for (int i = 0; i < n; i += 2) {
        if (comp[i] == comp[i + 1])
            return false;
        assignment[i / 2] = comp[i] > comp[i + 1];
    }
    return true;
}

//add clause a==av|b==bv
void add(int a, int av, int b, int bv) {
    //a!=av ==> b==bv
    g[2 * a + av].push_back(2 * b + (1 ^ bv));
    //b!=bv ==> a==av
    g[2 * b + bv].push_back(2 * a + (1 ^ av));
    //in reverse graph
    gt[2 * b + (1 ^ bv)].push_back(2 * a + av);
    gt[2 * a + (1 ^ av)].push_back(2 * b + bv);
}

int s;
vector<vector<int>> r;
vector<int> clazz;

bool possible(int T) {
    g = vector<vector<int>>(2 * s, vector<int>());
    gt = vector<vector<int>>(2 * s, vector<int>());
    for (int i = 0; i < s; ++i) {
        for (int k = T; k < s - 1; ++k) {
            if (clazz[r[i][k]] == clazz[i]) {
                add(r[i][k], 0, i, 0);
                add(r[i][k], 1, i, 1);
            } else if (clazz[r[i][k]] == (clazz[i] + 1) % 3) {
                add(i, 1, r[i][k], 0);
            } else {
                add(r[i][k], 1, i, 0);
            }
        }
    }
    return solve_2SAT();
}

int main() {
    cin >> s;
    n = s * 2;
    int a;
    for (int i = 0; i < s; ++i) {
        cin >> a;
        clazz.push_back(a);
        r.push_back(vector<int>());
        for (int j = 0; j < s - 1; ++j) {
            cin >> a;
            r[i].push_back(a - 1);
        }
    }

    int lo = 0, hi = s - 1, mid;
    while (lo + 1 < hi) {
        mid = (lo + hi) >> 1;
        if (possible(mid)) hi = mid;
        else lo = mid;
    }
    if (possible(lo)) cout << lo << endl;
    else cout << hi << endl;

    return 0;
}
