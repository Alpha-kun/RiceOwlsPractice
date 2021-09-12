#include <bits/stdc++.h>

using namespace std;
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

bool marked[205];
vector<Edge *> graph[205];

int dfs(int s, int t, int f) {
    if (s == t) return f;
    marked[s] = true;
    for (Edge *edge : graph[s]) {
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


int n;
double d;

int x[101], y[101], p[101], m[101];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> n >> d;
    int mf = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> x[i] >> y[i] >> p[i] >> m[i];
        mf += p[i];
    }

    vector<Edge *> eg;
    for (int i = 1; i <= n; ++i) {
        if (p[i] > 0) {
            Edge *e = new Edge(0, i, p[i]);
            eg.push_back(e);
            graph[0].push_back(e);
            graph[i].push_back(e);
        }
        Edge *it = new Edge(i, 100 + i, m[i]);
        eg.push_back(it);
        graph[i].push_back(it);
        graph[100 + i].push_back(it);
        for (int j = i + 1; j <= n; ++j) {
            if ((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]) <= d * d) {
                Edge *e = new Edge(100 + i, j, INF);
                eg.push_back(e);
                graph[100 + i].push_back(e);
                graph[j].push_back(e);
                e = new Edge(100 + j, i, INF);
                eg.push_back(e);
                graph[100 + j].push_back(e);
                graph[i].push_back(e);
            }
        }
    }

//    cout << maxFlow(0, 5) << endl;
//    vector<int> ans;
    bool ok = false;
    for (int i = 1; i <= n; ++i) {
        if (maxFlow(0, i) == mf) {
            cout << i - 1 << ' ';
            ok = true;
        }
        for (Edge *e: eg) {
            e->f = 0;
        }
    }

    if (!ok) {
        cout << -1 << endl;
    }

    return 0;
}
