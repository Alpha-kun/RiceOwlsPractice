#include <bits/stdc++.h>

using namespace std;
using namespace rel_ops;

typedef long long ll;

double getdist(const pair<double, double> &b1, const pair<double, double> &b2) {
	return hypot(b2.first - b1.first, b2.second - b1.second);
}

array<pair<double, double>, 2> getcenters(const pair<double, double> &b1, const pair<double, double> &b2, double radius) {
	auto midpoint = make_pair((b1.first+b2.first) / 2, (b1.second + b2.second) / 2);
	double dist = getdist(b1, b2);
	auto normalized = make_pair((b2.first - b1.first)/dist, (b2.second - b1.second)/dist);
	double off = sqrt(radius*radius - dist*dist/4);
	return {make_pair(midpoint.first + normalized.second*off, midpoint.second - normalized.first*off),
		make_pair(midpoint.first - normalized.second*off, midpoint.second + normalized.first*off)};
}

int main() {
	int N; cin >> N;
	
	for (int h=0; h<N; ++h) {
		int M; double D; cin >> M >> D;
		
		vector<pair<double, double>> mosqs(M);
		for (auto &mosq: mosqs) cin >> mosq.first >> mosq.second;
		
		int runningMax = 1;
		
		for (int i=0; i<M; ++i) {
			for (int j=i+1; j<M; ++j) {
				auto centers = getcenters(mosqs[i], mosqs[j], D/2);
				int cnt1 = count_if(mosqs.begin(), mosqs.end(), [&](auto mosq) { return getdist(mosq, centers[0]) < D/2 + 1e-6; });
				int cnt2 = count_if(mosqs.begin(), mosqs.end(), [&](auto mosq) { return getdist(mosq, centers[1]) < D/2 + 1e-6; });
				runningMax = max({runningMax, cnt1, cnt2});
			}
		}
		
		cout << runningMax << endl;
	}

	return 0;
}
