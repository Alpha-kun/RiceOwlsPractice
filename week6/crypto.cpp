#include <bits/stdc++.h>

using namespace std;
using namespace rel_ops;

typedef long long ll;

constexpr ll MOD = 1000000007;

ll powmod(ll b, ll e, ll mod) {
	ll res = 1;
	for (ll i=0; i<e; ++i) {
		res *= b;
		res %= mod;
	}
	return res;
}

int main() {
	int N;cin>>N;
	
	string B; cin >> B;
	
	array<ll,3> numSubsets = {1,0,0};
	ll numZero = 0;
	
	for (char c: B) {
		int digit = c - '0';
		if (digit == 0) ++numZero;
		auto oldNumSubsets = numSubsets;
		for (int i=0; i<3; ++i) {
			numSubsets[i] += oldNumSubsets[(90 + i - digit) % 3];
			numSubsets[i] %= MOD;
		}
		//cout << numSubsets[0] << "," << numSubsets[1] << "," << numSubsets[2] << endl;
	}
	
	cout << (((numSubsets[0] - powmod(2, numZero, MOD)) % MOD + MOD) % MOD) << endl;
	
	return 0;
}
