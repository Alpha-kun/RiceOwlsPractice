#include <bits/stdc++.h>

using namespace std;
using namespace rel_ops;

typedef long long ll;

int main() {
	int T; cin >> T;
	
	for (int h=0;h<T;++h) {
		int K; cin >> K;
		
		vector<int> xs, ys;
		
		for (int i=0; i<K; ++i) {
			int x1,y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2;
			xs.push_back(x1);
			xs.push_back(x2);
			ys.push_back(y1);
			ys.push_back(y2);
		}
		
		sort(xs.begin(),xs.end()); sort(ys.begin(), ys.end());
		
		cout << "Case #" << (h+1) << ": " << xs[(xs.size()-1) / 2] << " " << ys[(ys.size()-1) / 2] << endl;
	}
	
	return 0;
}
