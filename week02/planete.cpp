#include <bits/stdc++.h>

using namespace std;
using namespace rel_ops;

typedef long long ll;

ll timeinterval(int d1, int m1, int d2, int m2) {
	struct tm t1 = {0}, t2 = {0};
	t1.tm_mon = m1 - 1;
	t1.tm_mday = d1;
	t2.tm_mon = m2 - 1;
	t2.tm_mday = d2;
	return ll(difftime(mktime(&t2), mktime(&t1)) / 86400);
}

template <class T>
T bezout(T a, T b, T &x, T &y) {
	T xx = y = 0;
	T yy = x = 1;
	while (b) {
		T q = a / b;
		T t = b; b = a%b; a = t;
		t = xx; xx = x - q*xx; x = t;
		t = yy; yy = y - q*yy; y = t;
	}
	return a;
}

template<class T>
T modinv(T a, T MOD) {
	T x, y;
	bezout(((a%MOD) + MOD)%MOD, MOD, x, y);
	return x % MOD;
}

void printcontents(const vector<vector<ll>> &V) {
	for (auto &row: V) {
		for (auto elem: row) cout << elem << " ";
		cout << endl;
	}
	cout << "---" << endl;
}

void gausselim(vector<vector<ll>> &V, ll MOD) {
	int cols = V[0].size();
	int curcol = 0;
	//printcontents(V);
	for (int row = 0; row < V.size(); ++row) {
		for ( ; curcol < cols; ++curcol) {
			for (int row2 = row; row2 < V.size(); ++row2) {
				if (V[row2][curcol] % MOD != 0) {
					swap(V[row], V[row2]);
					goto exitloop;
				}
			}
		}
		exitloop:
		if (curcol == cols) break;
		
		ll inv = modinv(V[row][curcol], MOD);
		for (int col = 0; col < cols; ++col) {
			V[row][col] *= inv;
			V[row][col] %= MOD;
		}
		for (int row2 = row+1; row2 < V.size(); ++row2) {
			ll scalar = V[row2][curcol];
			for (int col = 0; col < cols; ++col) {
				V[row2][col] -= V[row][col] * scalar;
				V[row2][col] %= MOD;
			}
		}
		
		++curcol;
		
		//printcontents(V);
	}
}

bool inconsistent(const vector<ll> &row, ll MOD) {
	bool res = true;
	for (int i=0; i<row.size()-1; ++i) res &= (row[i] % MOD == 0);
	res &= (row.back() % MOD != 0);
	return res;
}

vector<ll> solve(vector<vector<ll>> &V, ll MOD) {
	gausselim(V, MOD);
	
	int cols = V[0].size();
	vector<ll> res(cols - 1);
	for (int row = V.size()-1; row >= 0; --row) {
		if (inconsistent(V[row], MOD)) {
			return {};
		}
		
		int firstcol = -1;
		for (int col = 0; col < cols-1; ++col) {
			if (V[row][col] % MOD != 0) {
				if (firstcol < 0) {
					firstcol = col;
					res[firstcol] = V[row][cols-1];
				} else {
					res[firstcol] -= res[col] * V[row][col];
					res[firstcol] %= MOD;
				}
			}
		}
	}
	
	return res;
}

int main() {
	int N,M; cin >> N >> M;

#if 0
	vector<vector<ll>> V{{4,5},{6,1}};
	
	gausselim(V, 7);
#endif
	
	vector<vector<ll>> syseq(N, vector<ll>(M+1));
	
	for (auto &eq: syseq) {
		int d1, m1, d2, m2; cin >> d1 >> m1 >> d2 >> m2;
		eq[M] = timeinterval(d1, m1, d2, m2);
		for (int i=0; i<M; ++i) cin >> eq[i];
	}
	
	auto syseq2 = syseq;
	auto sols = solve(syseq, 5);
	auto sols2 = solve(syseq2, 73);
	//printcontents(syseq);
	//printcontents(syseq2);
	if (sols.empty() || sols2.empty()) {
		cout << -1 << endl;
	} else {
		for (int i=0; i<M; ++i) {
			ll rawres = (sols[i] * modinv(73,5) * 73 + sols2[i] * modinv(5,73) * 5) % 365;
			cout << ((rawres + 365 + 364) % 365 + 1);
			if (i != M-1) cout << " ";
		}
		cout << endl;
	}
	

	return 0;
}
