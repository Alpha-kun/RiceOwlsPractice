#include <bits/stdc++.h>

using namespace std;
using namespace rel_ops;

typedef long long ll;

typedef bitset<128> color_t;

color_t FEN_sum(const vector<color_t> &FEN, int idx, int jdx) {
    color_t runningSum = 0;
    while (jdx > idx) {
        runningSum ^= FEN[jdx-1];
        jdx -= jdx & (-jdx);
    }
    while (idx > jdx) {
        runningSum ^= FEN[idx-1];
        idx -= idx & (-idx);
    }
    return runningSum;
}

color_t FEN_sum(const vector<color_t> &FEN, int idx) {
    return FEN_sum(FEN, 0, idx);
}

void FEN_update(vector<color_t> &FEN, int idx, color_t incr) {
    while (idx < FEN.size()) {
        FEN[idx] ^= incr;
        idx += (idx+1) & ( -(idx+1) );
    }
}

int main() {
	int N,Q; cin >> N >> Q;
	
	vector<int> colors(N);
	for (int &color: colors) { cin >> color; --color; }
	
	vector<vector<int>> graph(N);
	for (int i=1; i<N; ++i) {
		int pi; cin >> pi; --pi;
		graph[pi].push_back(i);
	}
	
	vector<pair<int, int>> eulerBounds(N, {-1, -1});
	int idx = 0;
	
	function<void(int)> fn = [&](int v) {
		eulerBounds[v].first = idx++;
		for (int n: graph[v]) fn(n);
		eulerBounds[v].second = idx;
	};
	fn(0);
	
	vector<color_t> FEN(N);
	for (int i=0; i<N; ++i) {
		color_t color;
		color[colors[i]] = 1;
		FEN_update(FEN, eulerBounds[i].first, color);
	}
	
	for (int i=0; i<Q; ++i) {
		int K,X; cin >> K >> X; --X;
		if (K == 0) {
			//cout << eulerBounds[X].first << " " << eulerBounds[X].second << endl;
			cout << FEN_sum(FEN, eulerBounds[X].first, eulerBounds[X].second).count() << endl;
		} else {
			color_t color;
			color[K - 1] = 1;
			FEN_update(FEN, eulerBounds[X].first, color ^ FEN_sum(FEN, eulerBounds[X].first, eulerBounds[X].first+1));
		}
	}

	return 0;
}
