#include <bits/stdc++.h>

using namespace std;
using namespace rel_ops;

typedef long long ll;

constexpr int INF = 1000000000;

int OFFS[][2] = {{-1,0},{1,0},{0,-1},{0,1}};

int enemyDists[1000][1000];
int dists[1000][1000];
int physDists[1000][1000];

int main() {
	int N,X,Y; cin >> N >> X >> Y;
	
	int xi,yi,xr,yr; cin>>xi>>yi>>xr>>yr;
	
	for (int i=0; i<X; ++i) {
		for (int j=0; j<Y; ++j) {
			enemyDists[i][j] = INF;
		}
	}
	
	queue<pair<int,int>> Q;
	
	for (int i=0; i<N; ++i) {
		int x,y; cin >> x >> y;
		Q.emplace(x,y);
		enemyDists[x][y] = 0;
	}
	
	while (!Q.empty()) {
		auto cur = Q.front(); Q.pop();
		for (auto &off: OFFS) {
			int nx = cur.first + off[0], ny = cur.second + off[1];
			if (nx >= 0 && ny >= 0 && nx < X && ny < Y && enemyDists[nx][ny] == INF) {
				enemyDists[nx][ny] = enemyDists[cur.first][cur.second]+1;
				Q.emplace(nx, ny);
			}
		}
	}
	
	for (int i=0; i<X; ++i) {
		for (int j=0; j<Y; ++j) {
			dists[i][j] = -1;
		}
	}
	
	priority_queue<tuple<int, int, int>> PQ;
	PQ.emplace(enemyDists[xi][yi], xi, yi);
	dists[xi][yi] = enemyDists[xi][yi];
	
	while (!PQ.empty()) {
		auto cur = PQ.top(); PQ.pop();
		for (auto &off: OFFS) {
			int nx = get<1>(cur) + off[0], ny = get<2>(cur) + off[1];
			if (nx >= 0 && ny >= 0 && nx < X && ny < Y) {
				int cand = min(get<0>(cur), enemyDists[nx][ny]);
				if (dists[nx][ny] < cand) {
					dists[nx][ny] = cand;
					PQ.emplace(cand, nx, ny);
				}
			}
		}
	}
	
	for (int i=0; i<X; ++i) {
		for (int j=0; j<Y; ++j) {
			physDists[i][j] = INF;
		}
	}
	queue<pair<int,int>> Q2;
	physDists[xi][yi] = 0;
	Q2.emplace(xi, yi);
	while (!Q2.empty()) {
		auto cur = Q2.front(); Q2.pop();
		for (auto &off: OFFS) {
			int nx = cur.first + off[0], ny = cur.second + off[1];
			if (nx >= 0 && ny >= 0 && nx < X && ny < Y && physDists[nx][ny] == INF && enemyDists[nx][ny] >= dists[xr][yr]) {
				physDists[nx][ny] = physDists[cur.first][cur.second]+1;
				Q2.emplace(nx, ny);
			}
		}
	}
	
	cout << dists[xr][yr] << " " << physDists[xr][yr] << endl;
	
	return 0;
}
