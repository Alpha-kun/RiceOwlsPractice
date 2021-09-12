#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll FEN_sum(const vector<ll> &FEN, int idx, int jdx) {
    ll runningSum = 0;
    while (jdx > idx) {
        runningSum += FEN[jdx-1];
        jdx -= jdx & (-jdx);
    }
    while (idx > jdx) {
        runningSum -= FEN[idx-1];
        idx -= idx & (-idx);
    }
    return runningSum;
}

ll FEN_sum(const vector<ll> &FEN, int idx) {
    return FEN_sum(FEN, 0, idx);
}

void FEN_update(vector<ll> &FEN, int idx, ll incr) {
    while (idx < FEN.size()) {
        FEN[idx] += incr;
        idx += (idx+1) & ( -(idx+1) );
    }
}

void FEN_rpupdate(vector<ll> &FEN, int idx, int jdx, ll incr) {
	FEN_update(FEN, idx, incr);
	if (jdx < FEN.size()) {
		FEN_update(FEN, jdx, -incr);
	}
}

ll FEN_rpquery(const vector<ll> &FEN, int idx) {
	return FEN_sum(FEN, idx+1);
}

void FEN_genupdate(vector<ll> &FEN1, vector<ll> &FEN2, int idx, int jdx, ll incr) {
	FEN_rpupdate(FEN1, idx, jdx, incr);
	FEN_update(FEN2, idx, incr * idx);
	if (jdx < FEN2.size()) {
		FEN_update(FEN2, jdx, -incr * jdx);
	}
}

ll FEN_gensum(const vector<ll> &FEN1, const vector<ll> &FEN2, int idx) {
	return FEN_rpquery(FEN1, idx) * idx - FEN_rpquery(FEN2, idx);
}

int main() {
	int N; cin >> N;
	
	vector<ll> FEN1(4000000), FEN2(4000000);
	
	for (int i=0; i<N; ++i) {
		ll Y,I,S,B; cin >> Y >> I >> S >> B;
		FEN_genupdate(FEN1, FEN2, B, B+1, S);
		if (I != 0) {
			FEN_genupdate(FEN1, FEN2, B+1, B+Y+1, I);
			ll maxForSpecies = S + Y*I;
			FEN_genupdate(FEN1, FEN2, B+Y+1, B+Y+1+maxForSpecies/I, -I);
			FEN_genupdate(FEN1, FEN2, B+Y+1+maxForSpecies/I, B+Y+2+maxForSpecies/I, -(maxForSpecies%I));
		}
	}
	
	ll runningMax = 0;
	
	for (int i=0; i<4000000; ++i) {
		runningMax = max(runningMax, FEN_gensum(FEN1, FEN2, i));
	}
	
	cout << runningMax << endl;
	
	return 0;
}
