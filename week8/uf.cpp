#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>

using namespace std;

template<class T>
struct UF {
	vector<T> links, sizes;
	UF(T N) : links(N), sizes(N, 1) {
		iota(links.begin(), links.end(), 0);
	}
	T find(T i) {
		if (links[i] != i) {
			links[i] = find(links[i]);
		}
		return links[i];
	}
	void merge(T i, T j) {
		i = find(i); j = find(j);
		if (i == j) return;
		if (sizes[i] < sizes[j]) {
			swap(i, j);
		}
		links[j] = i;
		sizes[i] += sizes[j];
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(NULL);
	
	int N,Q; scanf(" %d %d", &N, &Q);
	UF<int> uf(N);
	
	for (int i=0; i<Q; ++i) {
		char c; int A,B;
		scanf(" %c %d %d", &c, &A, &B);
		if (c == '?') {
			puts(uf.find(A) == uf.find(B) ? "yes" : "no");
		} else uf.merge(A,B);
	}
	
	return 0;
}
