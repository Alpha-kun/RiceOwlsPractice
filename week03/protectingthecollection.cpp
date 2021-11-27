#include <bits/stdc++.h>
using namespace std;
char mp[2005][2005];
bool vis[2005][2005];
int diRec[2005][2005];
char temp[3];
int ddi[4][2] = {-1, 0, 0, 1, 1, 0, 0, -1};
int main() {
    int n, r, c;
    scanf("%d%d%d", &n, &c, &r);
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= n; ++ j) {
            scanf("%s", temp);
            mp[i][j] = temp[0];
        }
    }
    int x = 1, y = c, di = 3;
    while (x != 0 && x != (n + 1) && y != 0 && y != (n + 1)) {
        vis[x][y] = true;
        diRec[x][y] = di;
        // cout << x << " " << y << endl;
        if (mp[x][y] == '\\') {
            if (di == 1) {
                di = 4;
            } else if (di == 2) {
                di = 3;
            } else if (di == 3) {
                di = 2;
            } else {
                di = 1;
            }
        } else if (mp[x][y] == '/') {
            if (di == 1) {
                di = 2;
            } else if (di == 2) {
                di = 1;
            } else if (di == 3) {
                di = 4;
            } else {
                di = 3;
            }
        }
        int _x = x + ddi[di - 1][0], _y = y + ddi[di - 1][1];
        x = _x, y = _y;
    }
    x = r, y = n, di = 4;
    bool flag = false;
    // cout << endl;
    while (x != 0 && x != (n + 1) && y != 0 && y != (n + 1)) {
        // cout << x << " " << y << endl;
        if (vis[x][y] == true) {
            if (mp[x][y] == '.' && diRec[x][y] == di) {

            } else if (mp[x][y] == '\\' && !
                    ((diRec[x][y] == 1 && di == 2) 
                    || (diRec[x][y] == 2 && di == 1)
                    || (diRec[x][y] == 3 && di == 4)
                    || (diRec[x][y] == 4 && di == 3))) {
                
            } else if (mp[x][y] == '/' && !
                    ((diRec[x][y] == 1 && di == 4) 
                    || (diRec[x][y] == 4 && di == 1)
                    || (diRec[x][y] == 3 && di == 2)
                    || (diRec[x][y] == 2 && di == 3))) {

            } else {
                flag = true;
                break;
            }
        }
        if (mp[x][y] == '\\') {
            if (di == 1) {
                di = 4;
            } else if (di == 2) {
                di = 3;
            } else if (di == 3) {
                di = 2;
            } else {
                di = 1;
            }
        } else if (mp[x][y] == '/') {
            if (di == 1) {
                di = 2;
            } else if (di == 2) {
                di = 1;
            } else if (di == 3) {
                di = 4;
            } else {
                di = 3;
            }
        }
        int _x = x + ddi[di - 1][0], _y = y + ddi[di - 1][1];
        x = _x, y = _y;
    }
    if (flag) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    return 0;
}
