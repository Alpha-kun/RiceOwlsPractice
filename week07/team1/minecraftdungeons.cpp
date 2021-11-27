#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;
typedef pair<pii, pii> pos;

int n, m, e;
char maze[30][30];

int dx[5] = {0,1, 0, -1, 0};
int dy[5] = {0,0, 1, 0, -1};

pos move(pos u, int d) {
    pii p = u.first;
    pii c = u.second;
    if (p.first + dx[d] < 0 || p.first + dx[d] >= n || p.second + dy[d] < 0 || p.second + dy[d] >= m)
        return make_pair(make_pair(-1, -1), make_pair(-1, -1));
    if (maze[p.first + dx[d]][p.second + dy[d]] == 'X') return make_pair(make_pair(-1, -1), make_pair(-1, -1));

    int xdif = p.first - c.first, ydif = p.second - c.second;
    p = make_pair(p.first + dx[d], p.second + dy[d]);
    if (abs(xdif) > abs(ydif)) {
        int cdx = xdif > 0 ? 1 : -1;
        if (maze[c.first + cdx][c.second] != 'X') return make_pair(p, make_pair(c.first + cdx, c.second));
        int cdy = ydif > 0 ? 1 : ydif < 0 ? -1 : 0;
        if (maze[c.first][c.second + cdy] != 'X') return make_pair(p, make_pair(c.first, c.second + cdy));
        return make_pair(p, c);
    } else if (abs(xdif) < abs(ydif)) {
        int cdy = ydif > 0 ? 1 : -1;
        if (maze[c.first][c.second + cdy] != 'X') return make_pair(p, make_pair(c.first, c.second + cdy));
        int cdx = xdif > 0 ? 1 : xdif < 0 ? -1 : 0;
        if (maze[c.first + cdx][c.second] != 'X') return make_pair(p, make_pair(c.first + cdx, c.second));
        return make_pair(p, c);
    } else {
        int cdx = xdif > 0 ? 1 : -1;
        if (maze[c.first + cdx][c.second] != 'X') return make_pair(p, make_pair(c.first + cdx, c.second));
        int cdy = ydif > 0 ? 1 : ydif < 0 ? -1 : 0;
        if (maze[c.first][c.second + cdy] != 'X') return make_pair(p, make_pair(c.first, c.second + cdy));
        return make_pair(p, c);
    }
}

bool valid(pos state) {
    pii p = state.first;
    pii c = state.second;
    return !(abs(p.first - c.first) <= e && abs(p.second - c.second) <= e);
}

//void show(pos p) {
//    cout << "(" << p.first.first << ',' << p.first.second << ") (" << p.second.first << ',' << p.second.second << ")"
//         << endl;
//}

int main() {
    cin >> n >> m >> e;
    string line;
    pos s = make_pair(make_pair(0, 0), make_pair(0, 0));
    pii dest;
    for (int i = 0; i < n; ++i) {
        cin >> line;
        for (int j = 0; j < m; ++j) {
            if (line[j] == 'X') maze[i][j] = 'X';
            else {
                maze[i][j] = '.';
                if (line[j] == 'P') s.first = make_pair(i, j);
                if (line[j] == 'C') s.second = make_pair(i, j);
                if (line[j] == 'E') dest = make_pair(i, j);
            }
        }
    }
    if (!valid(s)) {
        cout << "you're toast" << endl;
        return 0;
    }

//BFS
    bool visited[30][30][30][30];
    memset(visited, false, sizeof(visited));
    int dist[30][30][30][30];
    memset(dist, 0, sizeof(dist));

    list<pos> q;
    q.push_back(s);

    visited[s.first.first][s.first.second][s.second.first][s.second.second] = true;
    while (!q.empty()) {
        pos u = q.front();
        q.pop_front();
        for (int i = 0; i < 5; i++) {
            pos v = move(u, i);
            if (!valid(v)) continue;
            if (v.first.first == -1) continue;
            if (!visited[v.first.first][v.first.second][v.second.first][v.second.second]) {
                visited[v.first.first][v.first.second][v.second.first][v.second.second] = true;
                q.push_back(v);
                dist[v.first.first][v.first.second][v.second.first][v.second.second] =
                        dist[u.first.first][u.first.second][u.second.first][u.second.second] + 1;
            }
        }
    }

    int ans = 1000000000;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (visited[dest.first][dest.second][i][j]) {
                ans = min(ans, dist[dest.first][dest.second][i][j]);
            }
        }
    }
    if (ans == 1000000000) cout << "you're toast" << endl;
    else cout << ans << endl;
    return 0;
}
