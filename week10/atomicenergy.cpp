#define _USE_MATH_DEFINES

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
	int N,Q; cin >> N >> Q;
	
	ll baseEnergy[101] = {0};
	int bestEnergyPerNeutronI = -1;
	double bestEnergyPerNeutron = numeric_limits<double>::infinity();
	for (int i=1; i<=N; ++i) {
		cin >> baseEnergy[i];
		if ((double(baseEnergy[i]) / i - bestEnergyPerNeutron) < -1e-9) {
			bestEnergyPerNeutron = double(baseEnergy[i]) / i;
			bestEnergyPerNeutronI = i;
		}
	}
	
	ll precalc[100000] = {0};
	for (int i=1; i<100000; ++i) {
		if (i <= N) precalc[i] = baseEnergy[i];
		else {
			precalc[i] = numeric_limits<ll>::max();
			for (int j=1; j<=N; ++j) {
				precalc[i] = min(precalc[i], precalc[i-j] + baseEnergy[j]);
			}
		}
	}
	
	for (int i=0; i<Q; ++i) {
		int K; cin >> K;
		if (K < 100000) {
			cout << precalc[K] << endl;
		} else {
			int numDup = (K - 99999 + bestEnergyPerNeutronI - 1) / bestEnergyPerNeutronI;
			//cout << bestEnergyPerNeutronI << endl;
			//cout << precalc[ (K - numDup * bestEnergyPerNeutronI) ] << endl;
			cout << (precalc[K - numDup * bestEnergyPerNeutronI] + numDup * baseEnergy[bestEnergyPerNeutronI]) << endl;
		}
	}
	
	return 0;
}
