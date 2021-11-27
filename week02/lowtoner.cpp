#include <bits/stdc++.h>

using namespace std;

struct Node {
    Node *ch[26];
    bool mark = false;

    Node() {
        for (int i = 0; i < 26; ++i) ch[i] = nullptr;
    }
};

struct State {
    Node *r;
    vector<int> seq;
};

Node *rt = new Node();

vector<int> match[26];

int id(int c) {
    return c - 'A';
}

void testcase(string &s) {
    vector<State> states(1, {rt, vector<int>(0)});
    for (int i = 0; i < s.size(); ++i) {
        vector<State> next;
        if (s[i] == ' ') {
            for (State st: states) {
                if (st.r->mark) {
                    vector<int> nseq = st.seq;
                    nseq.push_back(id(' '));
                    next.push_back({rt, nseq});
                }
                for (int j = 0; j < 26; ++j) {
                    if (st.r->ch[j] != nullptr) {
                        vector<int> nseq = st.seq;
                        nseq.push_back(j);
                        next.push_back({st.r->ch[j], nseq});
                    }
                }
            }
        } else {
            for (State st: states) {
                for (int c: match[id(s[i])]) {
                    if (st.r->ch[c] != nullptr) {
                        vector<int> nseq = st.seq;
                        nseq.push_back(c);
                        next.push_back({st.r->ch[c], nseq});
                    }
                }
            }
        }
        states = next;
    }

    vector<string> ans;
    for (State st: states) {
        if (st.r->mark) {
            for (int c: st.seq) {
                cout << (char) (c + 'A');
            }
            cout << endl;
        }
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    match[id('C')].push_back(id('O'));
    match[id('C')].push_back(id('Q'));
    match[id('C')].push_back(id('G'));
    match[id('O')].push_back(id('Q'));

    match[id('F')].push_back(id('P'));
    match[id('F')].push_back(id('E'));
    match[id('F')].push_back(id('R'));
    match[id('F')].push_back(id('B'));
    match[id('P')].push_back(id('R'));
    match[id('P')].push_back(id('B'));
    match[id('E')].push_back(id('B'));

    match[id('I')].push_back(id('T'));
    match[id('V')].push_back(id('M'));

    for (int i = 0; i < 26; ++i) {
        match[i].push_back(i);
        sort(match[i].begin(), match[i].end());
    }

    int n;
    cin >> n;
    string s;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        Node *curr = rt;
        for (int j = 0; j < s.size(); ++j) {
            if (curr->ch[id(s[j])] == nullptr) {
                curr->ch[id(s[j])] = new Node();
            }
            curr = curr->ch[id(s[j])];
            if (j == s.size() - 1) {
                curr->mark = true;
            }
        }
    }

//    string t = "   P";
//    testcase(t);

    while (getline(cin, s)) {
        testcase(s);
        cout << endl;
    }
    return 0;
}
