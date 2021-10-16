#include <bits/stdc++.h>

using namespace std;
using namespace rel_ops;

typedef long long ll;

int main() {
	int T; cin >> T;
	
	for (int h=0;h<T;++h) {
		int N,A; cin >> N >> A;
		
		cout << "Case #" << (h+1) << ": ";
		
		if (A > N - 3) {
			cout << "POSSIBLE" << endl;
			if (N == 4) {
				cout << 0 << " " << 0 << endl;
				cout << (A/2) << " " << 0 << endl;
				cout << (A - A/2) << " " << 1 << endl;
				cout << 0 << " " << 1 << endl;
			} else {
				deque<array<ll,2>> points = {{1, -(A - N + 2)}};
				int i;
				for (i=1; points.size() < N-1; ++i) {
					points.push_front({i%2 ? 1 : 0,i});
					points.push_back({i%2 ? 2 : 1,i});
				}
				if (N % 2 == 0) {
					points.push_back({1,i});
				}
				for (auto point: points) {
					cout << point[0] << " " << (point[1] + (A - N + 2)) << endl;
				}
			}
		} else cout << "IMPOSSIBLE" << endl;
	}
	
	return 0;
}
