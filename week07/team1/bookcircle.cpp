#include <bits/stdc++.h>

using namespace std;

#define MAXN 2005
#define INF 1000000009
typedef pair<int, int> pii;

struct Edge {
    int v, w, cap, f;

    Edge(int a, int b, int c) : v(a), w(b), cap(c), f(0) {}

    int other(int s) { return s == v ? w : v; }

    int getRez(int s) { return s == v ? cap - f : f; }

    void addFlow(int s, int d) {
        if (s == v) f += d;
        else f -= d;
    }
};

bool marked[MAXN];
vector<Edge *> graph[MAXN];

int dfs(int s, int t, int f) {
    if (s == t) return f;
    marked[s] = true;
    for (Edge *edge: graph[s]) {
        int to = edge->other(s);
        if (!marked[to] && edge->getRez(s) > 0) {
            int d = dfs(to, t, min(f, edge->getRez(s)));
            if (d > 0) {
                edge->addFlow(s, d);
                return d;
            }
        }
    }
    return 0;
}

int maxFlow(int s, int t) {
    int totalFlow = 0;
    while (true) {
        memset(marked, false, sizeof(marked));
        int inc = dfs(s, t, INF);
        if (inc == 0) break;
        totalFlow += inc;
    }
    return totalFlow;
}

int main() {
    int b, g;
    cin >> b >> g;

    map<string, int> bname, gname;
    map<string, vector<string>> bookbg;
    string student, book;
    int c = 0;
    int n;
    for (int i = 0; i < b; ++i) {
        cin >> student >> n;
        if (bname.find(student) == bname.end()) {
            bname[student] = c++;
        }
        for (int j = 0; j < n; ++j) {
            cin >> book;
            bookbg[book] = vector<string>(1, student);
        }
        Edge *e = new Edge(2002, i, 1);
        graph[2002].push_back(e);
        graph[i].push_back(e);
    }

    c = 0;
    for (int i = 0; i < g; ++i) {
        cin >> student >> n;
        if (gname.find(student) == gname.end()) {
            gname[student] = c++;
        }
        for (int j = 0; j < n; ++j) {
            cin >> book;
            bookbg[book].push_back(student);
        }
        Edge *e = new Edge(b + i, 2003, 1);
        graph[b + i].push_back(e);
        graph[2003].push_back(e);
    }

    set<pii> S;

    for (auto it = bookbg.begin(); it != bookbg.end(); ++it) {
        string bkname = it->first;
        vector<string> pr = it->second;
        int bid = bname[pr[0]], gid = gname[pr[1]];
        if (S.find(make_pair(bid, gid)) == S.end()) {
            Edge *e = new Edge(bid, b + gid, 1);
//            cout << bid << '-' << b + gid << endl;
            graph[bid].push_back(e);
            graph[b + gid].push_back(e);
        }
    }

    int ans = maxFlow(2002, 2003);
    cout << ans << endl;
    return 0;
}
