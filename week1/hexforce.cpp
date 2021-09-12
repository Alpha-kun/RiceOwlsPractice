#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int OFFS[][2] = {{-1,0},{1,0},{-1,-1},{0,-1},{1,1},{0,1}};

constexpr int INF = 1000000000;

struct edge_t {
	int cap = 0;
	int flow = 0;
	int cost = 0;
};

int minCostMatch(const vector<vector<int>> &table, int fromSize, int toSize) {
	vector<unordered_map<int, edge_t>> graph(fromSize + toSize + 2);
	int start = fromSize + toSize;
	int finish = fromSize + toSize + 1;
	for (int i=0; i<fromSize; ++i) {
		for (int j=0; j<toSize; ++j) {
			graph[i][fromSize + j] = {1, 0, table[i][j]};
			graph[fromSize + j][i] = {0, 0, -table[i][j]};
		}
	}
	for (int i=0; i<fromSize; ++i) {
		graph[start][i] = {1, 0, 0};
	}
	for (int j=0; j<toSize; ++j) {
		graph[fromSize + j][finish] = {1, 0, 0};
	}
	
	int result = 0;
	for (;;) {
		vector<int> prev(graph.size(), -1);
		vector<int> dists(graph.size(), INF);
		queue<int> Q;
		vector<bool> inQ(graph.size());
		
		Q.push(start);
		dists[start] = 0;
		inQ[start] = true;
		
		while (!Q.empty()) {
			int cur = Q.front(); Q.pop();
			for (auto &nxt: graph[cur]) {
				int cand = dists[cur] + nxt.second.cost;
				if (nxt.second.cap > nxt.second.flow && dists[nxt.first] > cand) {
					dists[nxt.first] = cand;
					Q.push(nxt.first);
					inQ[nxt.first] = true;
					prev[nxt.first] = cur;
				}
			}
		}
		
		if (prev[finish] == -1) {
			break; // no augmenting path
		}

		int dflow = INF;
		// find the max flow for this path
		for (int node=finish; prev[node] != -1; node=prev[node]) {
			dflow = min(dflow, graph[prev[node]][node].cap - graph[prev[node]][node].flow);
		}
		// update 
		for (int node=finish; prev[node] != -1; node=prev[node]) {	
			graph[prev[node]][node].flow += dflow;
			graph[node][prev[node]].flow -= dflow;
		}
		result += dists[finish] * dflow;
	}
	
	return result;
}

int main() {
	int N; cin >> N;
	
	for (int i=0; i<N; ++i) {
		vector<int> starts, values;
		for (;;) {
			int start; cin >> start;
			starts.push_back(start);
			if (cin.get() == '\n') {
				break;
			}
		}
		
		int S = starts.size();
		
		values = vector<int>(S);
		for (int &value: values) cin >> value;
		
		vector<vector<int>> hexagon;
		
		int id = 1;
		for (int j=(S+1)/2; j<=S; ++j) {
			hexagon.emplace_back(S);
			iota(hexagon.back().begin(), hexagon.back().begin() + j, id);
			id += j;
		}
		for (int j=S-1; j>=(S+1)/2; --j) {
			hexagon.emplace_back(S);
			iota(hexagon.back().end() - j, hexagon.back().end(), id);
			id += j;
		}
		
		vector<vector<int>> graph(id);
		
		for (int j=0; j<S; ++j) {
			for (int k=0; k<S; ++k) {
				if (hexagon[j][k] <= 0) continue;
				for (auto &off: OFFS) {
					int jp = j+off[0], kp = k+off[1];
					if (jp >= 0 && kp >= 0 && jp < S && kp < S && hexagon[jp][kp] > 0) {
						graph[hexagon[j][k]].push_back(hexagon[jp][kp]);
					}
				}
			}
		}
		
		/*
		for (int j=1; j<id; ++j) {
			cout << j << ": ";
			for (int el: graph[j]) cout << el << " ";
			cout << endl;
		}*/
		
		unordered_map<int, vector<int>> shortest_paths;
		for (int j=0; j<S; ++j) {
			shortest_paths[starts[j]] = vector<int>(id, INF);
			//shortest_paths[hexagon[j][j]] = shortest_paths[hexagon[j][(S+1)/2]] = shortest_paths[hexagon[(S+1)/2][j]] = vector<int>(id, INF);
		}
		
		for (auto &el: shortest_paths) {
			queue<int> Q;
			Q.push(el.first);
			el.second[el.first] = 0;
			while (!Q.empty()) {
				int cur = Q.front(); Q.pop();
				for (int nxt: graph[cur]) {
					if (el.second[nxt] == INF) {
						el.second[nxt] = el.second[cur] + 1;
						Q.push(nxt);
					}
				}
			}
		}
		
		vector<vector<int>> table1, table2, table3;
		table1 = table2 = table3 = vector<vector<int>>(S, vector<int>(S));
		for (int j=0; j<S; ++j) {
			for (int k=0; k<S; ++k) {
				table1[j][k] = values[j] * shortest_paths[starts[j]][hexagon[k][k]];
				table2[j][k] = values[j] * shortest_paths[starts[j]][hexagon[k][(S-1)/2]];
				table3[j][k] = values[j] * shortest_paths[starts[j]][hexagon[(S-1)/2][k]];
				
				//cout << j << "," << k << ": " << table1[j][k] << ", " << table2[j][k] << ", " << table3[j][k] << endl;
			}
		}
		
		cout << "Case #" << (i+1) << ": " << min({minCostMatch(table1, S, S), minCostMatch(table2, S, S), minCostMatch(table3, S, S)}) << endl;
	}
	
	return 0;
}
