#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
	ll N; cin >> N;
	
	ll lo=1, hi=N+1;
	
	for (;;) {
		if (lo+1 == hi) {
			cout << "A " << lo << endl;
			break;
		} else {
			lo = max(lo-1, 1LL);
			hi = min(hi+1, N+1);
		}
		
		if (hi-lo <= 3) {
			cout << "Q " << lo << " " << lo << " " << (lo+1) << " " << (lo+1) << endl;
			int rustle1, rustle2; cin >> rustle1 >> rustle2;
			if (rustle1) {
				tie(lo,hi) = make_tuple(lo,lo+1);
			} else if (rustle2) {
				tie(lo,hi) = make_tuple(lo+1,lo+2);
			} else {
				tie(lo,hi) = make_tuple(lo+2,hi);
			}
		} else {
			ll lomid = lo + (hi-lo)/4;
			ll mid = lo + (hi-lo)/2;
			ll himid = lo + (3*(hi-lo))/4;
			cout << "Q " << lo << " " << (mid-1) << " " << lomid << " " << (himid-1) << endl;
			int rustle1, rustle2; cin >> rustle1 >> rustle2;
			if (rustle1 && rustle2) {
				tie(lo,hi) = make_tuple(lomid, mid);
			} else if (rustle1) {
				tie(lo,hi) = make_tuple(lo, lomid);
			} else if (rustle2) {
				tie(lo,hi) = make_tuple(mid, himid);
			} else {
				tie(lo,hi) = make_tuple(himid, hi);
			}
		}
	}
	
	return 0;
}
