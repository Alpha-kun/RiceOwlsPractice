#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

vector<string> vec;

int main() {
    vec.push_back("L");
    while (vec.back().length() <= 20000) {
        auto temp = vec.back();
        reverse(temp.begin(), temp.end());
        for (int i = 0; i < temp.length(); ++ i) {
            temp[i] = temp[i] == 'L' ? 'R' : 'L';
        }
        vec.push_back(vec.back() + "L" + temp);
    }
    int T, n;
    string S;
    cin >> T;
    for (int _ = 1; _ <= T; ++ _) {
        cout << "Case " << _ << ": ";
        cin >> n >> S;
        if (vec[min(n - 1, (int)vec.size() - 1)].find(S) == string::npos) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
        }
    }
    return 0;
}
