#include <bits/stdc++.h>

using namespace std;
using namespace rel_ops;

typedef long long ll;
constexpr ll INF = 1000000000000000000;

struct suffix {
	int idx;
	array<int, 2> rank; 
};

bool operator<(const suffix &A, const suffix &B) { return A.rank < B.rank; }
bool operator==(const suffix &A, const suffix &B) { return A.rank == B.rank; }
using namespace rel_ops;

template<class RAIt, class RAOutIt>
void genSuffixArray(RAIt in1, RAIt in2, RAOutIt out) {
	for (auto it=in1; it<in2; ++it) {
		(out+(it-in1))->idx = it-in1;
		(out+(it-in1))->rank = {*it, it+1<in2 ? *(it+1) : numeric_limits<int>::min()};
	}
	
	sort(out, out+(in2-in1));
	
	vector<int> inds(in2-in1);
	
	for (int k=4; k<2*(in2-in1); k*=2) {
		int rank = 0, prevRank = out->rank[0];
		out->rank[0] = rank;
		inds[out->idx] = 0;
		
		for (int i=1; i<in2-in1; ++i) {
			if ((out+i)->rank[0] == prevRank && (out+i)->rank[1] == (out+i-1)->rank[1]) {
				prevRank = (out+i)->rank[0];
				(out+i)->rank[0] = rank;
			} else {
				prevRank = (out+i)->rank[0];
				(out+i)->rank[0] = ++rank;
			}
			inds[(out+i)->idx] = i;
		}
		
		for (int i=0; i<in2-in1; ++i) {
			int nextIndex = (out+i)->idx + k/2;
			(out+i)->rank[1] = nextIndex < in2-in1 ? (out+inds[nextIndex])->rank[0] : numeric_limits<int>::min();
		}
		
		sort(out, out+(in2-in1));
	}
}

template<class RAStringIt, class RASuffIt, class RALCPIt>
void genLCP(RAStringIt in1, RAStringIt in2, RASuffIt suffs, RALCPIt lcp) {
	int N = in2-in1;
	vector<int> inv_suffix(N, 0);
	for (int i=0; i<N; ++i) {
		inv_suffix[suffs[i].idx] = i;
	}
	int k = 0;
	for (int i=0; i<N; ++i) {
		if (inv_suffix[i] == N-1) {
			k = 0;
			continue;
		}
		int j = suffs[inv_suffix[i]+1].idx;
		while (i+k<N && j+k<N && in1[i+k]==in1[j+k]) {
			++k;
		}
		lcp[inv_suffix[i]] = k;
		if (k > 0) {
			--k;
		}
	}
}

int main() {
	for (;;) {
		int N; cin >> N; if (N == 0) break;
		int halfN = (N+2)/2;
		
		string aggregate;
		vector<int> lifeformTable;
		
		if (N == 1) {
			string s; cin >> s;
			cout << s << endl << endl;
			continue;
		}
		
		for (int i=0; i<N; ++i) {
			string s; cin >> s; s += char(128 + i);
			aggregate += s;
			for (int j=0; j<s.length(); ++j) {
				lifeformTable.push_back(i);
			}
		}
		
		//cout << aggregate << endl;
		
		vector<suffix> suffixarr(aggregate.size());
		vector<int> lcp(aggregate.size());
		genSuffixArray(aggregate.begin(), aggregate.end(), suffixarr.begin());
		genLCP(aggregate.begin(), aggregate.end(), suffixarr.begin(), lcp.begin());
		
		/*
		for (auto &suffix: suffixarr) cout << aggregate.substr(suffix.idx) << " ";
		cout << endl;
		for (int v: lcp) cout << v << " ";
		cout << endl;
		*/
		
		map<int,int> lifeforms;
		map<int,int> commonprefs;
		int runningMax = 0;
		vector<int> runningMaxStarts;
		
		int lptr = 0, rptr = 0;
		for (;;) {
			while (rptr < aggregate.size() && lifeforms.size() < halfN) {
				++lifeforms[lifeformTable[suffixarr[rptr].idx]];
				++commonprefs[lcp[rptr]];
				++rptr;
			}
			//cout << lptr << ", " << rptr << endl;
			if (lifeforms.size() < halfN) break;
			if (--commonprefs[lcp[rptr-1]] == 0) commonprefs.erase(lcp[rptr-1]);
			int cand = commonprefs.begin()->first;
			if (runningMax <= cand) {
				if (runningMax < cand) {
					runningMaxStarts.clear();
				}
				runningMax = cand;
				//cout << runningMax << " " << lptr << endl;
				runningMaxStarts.push_back(suffixarr[lptr].idx);
			}
			++commonprefs[lcp[rptr-1]];
			if (--lifeforms[lifeformTable[suffixarr[lptr].idx]] == 0) {
				lifeforms.erase(lifeformTable[suffixarr[lptr].idx]);
			}
			if (--commonprefs[lcp[lptr]] == 0) commonprefs.erase(lcp[lptr]);
			++lptr;
		}
		
		//cout << runningMax << endl;
		
		if (runningMax == 0) {
			cout << "?" << endl;
		} else {
			string lastStr;
			for (int start: runningMaxStarts) {
				string cur = aggregate.substr(start, runningMax);
				if (cur != lastStr) {
					cout << cur << endl;
					lastStr = cur;
				}
			}
		}
		cout << endl;
	}
	
	return 0;
}
