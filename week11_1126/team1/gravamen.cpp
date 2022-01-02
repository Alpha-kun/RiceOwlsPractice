#include <bits/stdc++.h>

using namespace std;

#define MAXN 10000
#define INF 1000000009

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

int s, t, l;
vector<Edge *> edges;

bool possible(int m) {
    for (int i = 0; i < edges.size(); ++i) {
        edges[i]->f = 0;
        if (edges[i]->w == l + s + t + 1) edges[i]->cap = m;
    }
    return maxFlow(0, l + s + t + 1) >= l;
}

void display() {
    for (int i = 1; i <= l; ++i) {
        if (graph[i][0]->f == 1) cout << "INDV " << graph[i][0]->w - l << endl;
        else cout << "CORP " << graph[i][1]->w - l - s << endl;
    }
}

int main() {
    cin >> s >> t >> l;
    int u, v;
    for (int i = 1; i <= l; ++i) {
        cin >> u >> v;
        Edge *e = new Edge(i, l + u, 1);
        graph[i].push_back(e);
        graph[l + u].push_back(e);
        edges.push_back(e);
        e = new Edge(i, l + s + v, 1);
        graph[i].push_back(e);
        graph[l + s + v].push_back(e);
        edges.push_back(e);
    }
    for (int i = 1; i <= l; ++i) {
        Edge *e = new Edge(0, i, 1);
        graph[0].push_back(e);
        graph[i].push_back(e);
        edges.push_back(e);
    }
    for (int i = 1; i <= s + t; ++i) {
        Edge *e = new Edge(l + i, l + s + t + 1, 1);
        graph[l + i].push_back(e);
        graph[l + s + t + 1].push_back(e);
        edges.push_back(e);
    }

    int lo = 1, hi = l, mid;
    while (lo + 1 < hi) {
        mid = (lo + hi) >> 1;
        if (possible(mid)) hi = mid;
        else lo = mid;
    }

    if (!possible(lo)) possible(hi);
    display();

    return 0;
}
