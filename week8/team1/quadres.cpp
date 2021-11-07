#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

constexpr ll gcd(ll a, ll b) {
	return b == 0 ? a : gcd(b, a % b);
}

ll quadres(ll a, ll p, bool aprime = false) {
	a %= p;
	
	if (p == 2) {
		return a % p;
	}
	if (a == 0 || a == 1) {
		return a;
	}
	if (a == 2) {
		return ((p*p - 1) / 8) % 2 == 0 ? 1 : -1;
	}
	
	if (!aprime) {
		ll res = 1;
	
		ll qr2 = quadres(2, p, true);
		while (a % 2 == 0) {
			res *= qr2;
			a /= 2;
		}
		
		for (ll i=3; i*i <= a; i+=2) {
			if (a % i == 0) {
				ll qri = quadres(i, p, true);
				while (a % i == 0) {
					res *= qri;
					a /= i;
				}
			}
		}
		
		res *= quadres(a, p, true);
		return res;
	} else {
		return (((a-1) * (p-1) / 4) % 2 == 0 ? 1 : -1) * quadres(p, a);
	}
	
}

int main() {
	int N; cin >> N;
	
	for (int i=0; i<N; ++i) {
		ll a,p; cin >> a >> p;
		cout << (quadres(a,p) != -1 ? "yes" : "no") << endl;
	}
	
	return 0;
}
