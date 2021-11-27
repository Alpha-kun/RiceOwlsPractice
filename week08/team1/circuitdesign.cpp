#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

const int maxn = 1e3 + 9;
vector<int> graph[maxn];
double y[maxn], x[maxn];
int cnt = 0;
void dfs(int parent, int cur) {
    for (auto nxt : graph[cur]) {
        if (nxt == parent) continue;
        x[nxt] = x[cur] + cos(M_PI * cnt / 2000);
        y[nxt] = y[cur] + sin(M_PI * cnt / 2000);
        ++cnt;
        dfs(cur, nxt);
    }
}

int main() {
    int n, _x, _y;
    scanf("%d", &n);
    for (int i = 1; i < n; ++ i) {
        scanf("%d%d", &_x, &_y);
        graph[_x].push_back(_y);
        graph[_y].push_back(_x);
    }
    x[1] = y[1] = 0;
    dfs(0, 1);
    for (int i = 1; i <= n; ++ i) {
        printf("%.10lf %.10lf\n", x[i], y[i]);
    }
    return 0;
}