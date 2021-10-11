#include <bits/stdc++.h>

using namespace std;
using namespace rel_ops;

typedef long long ll;

array<int,2> offs[] = {{1,0},{-1,0},{0,1},{0,-1}};

int main() {
	int R,C; cin >> R >> C;
	
	cin.ignore();
	
	vector<string> V(R);
	for (auto &row: V) getline(cin, row);
	
	vector<vector<bool>> Aring(R, vector<bool>(C));
	vector<vector<bool>> Bring(R, vector<bool>(C));
	
	auto fillbounds = [&](int i, int j, vector<vector<bool>> &visited) {
		array<int,2> prevbestoff{0,0};
		for (;;) {
			visited[i][j] = true;
			bool intersection = true;
			array<int,2> bestoff{0,0};
			for (auto &off: offs) {
				int ip = i+off[0], jp = j+off[1];
				//cout << ip << " " << jp << endl;
				if (ip >= 0 && jp >= 0 && ip < R && jp < C && (V[ip][jp] == 'A' || V[ip][jp] == 'B' || V[ip][jp] == 'X')) {
					if (!visited[ip][jp]) bestoff = off;
				} else {
					intersection = false;
				}
			}
			if (bestoff == array<int,2>{0,0}) break;
			if (intersection) bestoff = prevbestoff;
			i += bestoff[0]; j += bestoff[1];
			prevbestoff = bestoff;
		}
	};
	
	for (int i=0; i<R; ++i) {
		for (int j=0; j<C; ++j) {
			if (V[i][j] == 'A') fillbounds(i,j,Aring);
			if (V[i][j] == 'B') fillbounds(i,j,Bring);
		}
	}
	
	vector<vector<int>> Azone(R, vector<int>(C));
	vector<vector<int>> Bzone(R, vector<int>(C));
	
	function<bool(int, int, vector<vector<int>> &, const vector<vector<bool>> &, int)> fillzone = [&](int i, int j, vector<vector<int>> &visited, const vector<vector<bool>> &boundary, int fillval) {
		visited[i][j] = fillval;
		bool inside = !(i == 0 || j == 0 || i == R-1 || j == C-1);
		for (auto &off: offs) {
			int ip = i+off[0], jp = j+off[1];
			if (ip >= 0 && jp >= 0 && ip < R && jp < C && !boundary[ip][jp] && !visited[ip][jp]) {
				inside &= fillzone(ip, jp, visited, boundary, fillval);
			}
		}
		return inside;
	};
	
	int fillno = 1, Ain, Bin;
	
	for (int i=0; i<R; ++i) {
		for (int j=0; j<C; ++j) {
			if (!Aring[i][j] && !Bring[i][j]) {
				if (!Azone[i][j] && fillzone(i,j,Azone,Aring,fillno)) {
					Ain = fillno;
				}
				if (!Bzone[i][j] && fillzone(i,j,Bzone,Bring,fillno)) {
					Bin = fillno;
				}
			}
			++fillno;
		}
	}
	
	int Acount = 0, Bcount = 0, ABcount = 0;
	
	for (int i=0; i<R; ++i) {
		for (int j=0; j<C; ++j) {
			if (V[i][j] == '.') {
				bool inA = Azone[i][j] == Ain;
				bool inB = Bzone[i][j] == Bin;
				if (inA && inB) ABcount++;
				else if (inA) Acount++;
				else if (inB) Bcount++;
			}
		}
	}
	
	cout << Acount << " " << Bcount << " " << ABcount << endl;
	
	return 0;
}
