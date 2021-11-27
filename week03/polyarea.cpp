#include <bits/stdc++.h>

using namespace std;
using namespace rel_ops;

typedef long long ll;

int main() {
	for (;;) {
		int N; cin >> N; if (N==0) break;
		
		vector<pair<double,double>> vertices(N);
		for (auto &v: vertices) {
			cin >> v.first >> v.second;
		}
		
		double area = 0;
		for (int i=0; i<N; ++i) {
			int j = (i+1)%N;
			area += (vertices[i].first * vertices[j].second - vertices[i].second * vertices[j].first)/2;
		}
		
		cout << (area < 0 ? "CW": "CCW") << " " << fixed << setprecision(1) << fabs(area) << endl;
	}
	

	return 0;
}
