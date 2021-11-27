#include <bits/stdc++.h>

using namespace std;
using namespace rel_ops;

typedef long long ll;

int main() {
	int N; cin >> N;
	
	vector<double> masses(N); for (auto &mass: masses) cin >> mass;
	
	double prevmass = masses[N-1];
	double pos = 0;
	
	for (int i=N-2; i>=1; --i) {
		pos = max({
			max(0.0, pos - 1) + prevmass/(prevmass + masses[i]),
			max(0.0, pos + 1) - prevmass/(prevmass + masses[i])
		});
		prevmass += masses[i];
	}
	
	cout << setprecision(17) << (pos + 1) << endl;
	
	return 0;
}
