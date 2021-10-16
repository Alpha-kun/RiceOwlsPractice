#include <bits/stdc++.h>

using namespace std;
using namespace rel_ops;

typedef long long ll;

int main() {
	int T; cin >> T;
	
	for (int h=0;h<T;++h) {
		int N,D,C,M;cin>>N>>D>>C>>M;
		
		string line; cin >> line;
		
		int dogFoodLeft = D, catFoodLeft = C;
		
		int i=0;
		for ( ; i<N; ++i) {
			if (line[i] == 'D') {
				if (dogFoodLeft == 0) break;
				--dogFoodLeft;
				catFoodLeft += M;
			} else {
				if (catFoodLeft == 0) break;
				--catFoodLeft;
			}
		}
		cout << "Case #" << (h+1) << ": ";
		for ( ; i<N; ++i) {
			if (line[i] == 'D') { cout << "NO" << endl; goto endloop; }
		}
		cout << "YES" << endl;
		endloop:;
	}
	
	return 0;
}
