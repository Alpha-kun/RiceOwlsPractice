#include <bits/stdc++.h>

using namespace std;
using namespace rel_ops;

typedef long long ll;
constexpr ll INF = 1000000000000000000;

struct cap_flow_t {
	ll cap = 0;
	ll flow = 0;
};

int main() {
	int N,M,C; cin >> N >> M >> C;
	
	vector<int> clients(C); unordered_map<int, int> vertexToClient;
	for (int &cli: clients) cin >> cli;
	for (int i=0; i<C; ++i) vertexToClient[clients[i]] = i;
	
	vector<vector<pair<ll, int>>> graph(N);
	
	for (int i=0; i<M; ++i) {
		int from, to; ll weight; cin >> from >> to >> weight;
		graph[from].emplace_back(weight, to);
	}
	
	vector<unordered_set<int>> revShortestPathGraph(N);
	vector<ll> dists(N, INF);
	priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> PQ;
	dists[0] = 0;
	PQ.emplace(0, 0);
	while (!PQ.empty()) {
		auto cur = PQ.top(); PQ.pop();
		for (auto &nxt: graph[cur.second]) {
			ll cand = cur.first + nxt.first;
			if (dists[nxt.second] > cand) {
				revShortestPathGraph[nxt.second] = {cur.second};
				dists[nxt.second] = cand;
				PQ.emplace(dists[nxt.second], nxt.second);
			} else if (dists[nxt.second] == cand) {
				revShortestPathGraph[nxt.second].insert(cur.second);
			}
		}
	}
	
#if 0
	for (int i=0; i<N; ++i) {
		cout << i << ": ";
		copy(revShortestPathGraph[i].begin(), revShortestPathGraph[i].end(), ostream_iterator<int>(cout, " "));
		cout << endl;
	}
#endif
	
	bool shortestPathGraph[1000][1000] = {{false}};
	for (int i=0; i<N; ++i) {
		for (int j: revShortestPathGraph[i]) {
			shortestPathGraph[j][i] = true;
		}
	}
	
	for (int k=0; k<N; ++k) {
		for (int i=0; i<N; ++i) {
			for (int j=0; j<N; ++j) {
				shortestPathGraph[i][j] |= shortestPathGraph[i][k] && shortestPathGraph[k][j];
			}
		}
	}

	int S = 2*C;
	int T = 2*C+1;

	vector<unordered_map<int, cap_flow_t>> flowgraph(2*C+2);
	for (int i=0; i<C; ++i) {
		for (int j=0; j<C; ++j) {
			if (shortestPathGraph[clients[i]][clients[j]]) {
				flowgraph[i][C+j].cap = 1;
			}
		}
		flowgraph[S][i].cap = 1;
		flowgraph[C+i][T].cap = 1;
	}
	
	ll max_flow = 0;
	for (;;) {
		// Do a BFS to find an augmenting path.
		vector<int> prev(flowgraph.size(), -1);
		queue<int> Q;
		Q.push(S);
		while (!Q.empty()) {
			int cur = Q.front(); Q.pop();
			for (auto &&next_info: flowgraph[cur]) {
				if (prev[next_info.first] == -1 && next_info.first != S && next_info.second.cap > next_info.second.flow) {
					Q.push(next_info.first);
					prev[next_info.first] = cur;
				}
			}
		}
	
		if (prev[T] == -1) {
			break; // no augmenting path
		}
	
		ll dflow = INF;
		// find the max flow for this path
		for (int node=T; prev[node] != -1; node=prev[node]) {
			dflow = min(dflow, flowgraph[prev[node]][node].cap - flowgraph[prev[node]][node].flow);
		}
		// update 
		for (int node=T; prev[node] != -1; node=prev[node]) {	
			flowgraph[prev[node]][node].flow += dflow;
			flowgraph[node][prev[node]].flow -= dflow;
		}
		max_flow += dflow;
	}
	
	cout << (C-max_flow) << endl;
	
	return 0;
}
