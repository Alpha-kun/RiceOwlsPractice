#include <bits/stdc++.h>
using namespace std;
int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
char mp[2][105][105];
int statusRing[2][105][105];
int r, c;
bool valid(int i, int j) {
    return 0 <= i && i < r && 0 <= j && j < c;
}
struct Node {
    int i, j, di, id;
    bool valid() {
        return 0 <= i && i < r && 0 <= j && j < c;
    }
    bool isX() {
        return mp[id][i][j] == 'X';
    }
    Node getDown() {
        return {i + 1, j, 0, id};
    }
    Node getUp() {
        return {i - 1, j, 1, id};
    }
    Node getRight() {
        return {i, j + 1, 2, id};
    }
    Node getLeft() {
        return {i, j - 1, 3, id};
    }
};
void drawRing(int i, int j, int c) {
    queue<Node> quu;
    quu.push({i, j, -1, c});
    char _c = c == 0 ? 'A' : 'B';
    int di;
    while (!quu.empty()) {
        auto cur = quu.front();
        quu.pop();
        auto leftNxt = cur.getLeft();
        auto rightNxt = cur.getRight();
        auto upNxt = cur.getUp();
        auto downNxt = cur.getDown();
        int cnt = leftNxt.isX() + rightNxt.isX() + upNxt.isX() + downNxt.isX();
        if (cur.di == -1) {
            if (leftNxt.isX()) {
                mp[leftNxt.id][leftNxt.i][leftNxt.j] = _c;
                quu.push(leftNxt);
            }
            if (rightNxt.isX()) {
                mp[rightNxt.id][rightNxt.i][rightNxt.j] = _c;
                quu.push(rightNxt);
            }
            if (upNxt.isX()) {
                mp[upNxt.id][upNxt.i][upNxt.j] = _c;
                quu.push(upNxt);
            }
            if (downNxt.isX()) {
                mp[downNxt.id][downNxt.i][downNxt.j] = _c;
                quu.push(downNxt);
            }
        } else if (cur.di == 0) {
            if (downNxt.isX()) {
                mp[downNxt.id][downNxt.i][downNxt.j] = _c;
                quu.push(downNxt);
            } else if(cnt <= 1) {
                if (leftNxt.isX()) {
                    mp[leftNxt.id][leftNxt.i][leftNxt.j] = _c;
                    quu.push(leftNxt);
                } else if (rightNxt.isX()) {
                    mp[rightNxt.id][rightNxt.i][rightNxt.j] = _c;
                    quu.push(rightNxt);
                } else if (upNxt.isX()) {
                    mp[upNxt.id][upNxt.i][upNxt.j] = _c;
                    quu.push(upNxt);
                }
            }
        } else if (cur.di == 1) {
            if (upNxt.isX()) {
                mp[upNxt.id][upNxt.i][upNxt.j] = _c;
                quu.push(upNxt);
            } else if(cnt <= 1) {
                if (leftNxt.isX()) {
                    mp[leftNxt.id][leftNxt.i][leftNxt.j] = _c;
                    quu.push(leftNxt);
                } else if (rightNxt.isX()) {
                    mp[rightNxt.id][rightNxt.i][rightNxt.j] = _c;
                    quu.push(rightNxt);
                } else if (downNxt.isX()) {
                    mp[downNxt.id][downNxt.i][downNxt.j] = _c;
                    quu.push(downNxt);
                }
            }
        } else if (cur.di == 2) {
            if (rightNxt.isX()) {
                mp[rightNxt.id][rightNxt.i][rightNxt.j] = _c;
                quu.push(rightNxt);
            } else if(cnt <= 1) {
                if (leftNxt.isX()) {
                    mp[leftNxt.id][leftNxt.i][leftNxt.j] = _c;
                    quu.push(leftNxt);
                } else if (downNxt.isX()) {
                    mp[downNxt.id][downNxt.i][downNxt.j] = _c;
                    quu.push(downNxt);
                } else if (upNxt.isX()) {
                    mp[upNxt.id][upNxt.i][upNxt.j] = _c;
                    quu.push(upNxt);
                }
            }
        } else if (cur.di == 3) {
            if (leftNxt.isX()) {
                mp[leftNxt.id][leftNxt.i][leftNxt.j] = _c;
                quu.push(leftNxt);
            } else if(cnt <= 1) {
                if (downNxt.isX()) {
                    mp[downNxt.id][downNxt.i][downNxt.j] = _c;
                    quu.push(downNxt);
                } else if (rightNxt.isX()) {
                    mp[rightNxt.id][rightNxt.i][rightNxt.j] = _c;
                    quu.push(rightNxt);
                } else if (upNxt.isX()) {
                    mp[upNxt.id][upNxt.i][upNxt.j] = _c;
                    quu.push(upNxt);
                }
            }
        }
    }
}
void dfs(int i, int j, int _c) {
    mp[_c][i][j] = 'O';
    for (int di = 0; di < 4; ++ di) {
        if (valid(i + dir[di][0], j + dir[di][1]) && mp[_c][i + dir[di][0]][j + dir[di][1]] == '.') {
            dfs(i + dir[di][0], j + dir[di][1], _c);
        }
    }
}
int main() {
    scanf("%d%d", &r, &c);
    for (int i = 0; i < r; ++ i) {
        scanf("%s", mp[0][i]);
        for (int j = 0; j < c; ++ j) {
            mp[1][i][j] = mp[0][i][j];
        }
    }
    bool findA = false, findB = false;
    for (int i = 0; i < r; ++ i) {
        for (int j = 0; j < c; ++ j) {
            if (mp[0][i][j] == 'A' && !findA) {
                drawRing(i, j, 0);
                findA = true;
            } else if (mp[1][i][j] == 'B' && !findB) {
                drawRing(i, j, 1);
                findB = true;
            }
        }
    }
    for (int i = 0; i < r; ++ i) {
        for (int j = 0; j < c; ++ j) {
            if (mp[0][i][j] != 'A') {
                mp[0][i][j] = '.';
            }
        }
    }
    for (int i = 0; i < r; ++ i) {
        for (int j = 0; j < c; ++ j) {
            if (mp[1][i][j] != 'B') {
                mp[1][i][j] = '.';
            }
        }
    }

    // for (int i = 0; i < r; ++ i) {
    //     for (int j = 0; j < c; ++ j) {
    //         cout << mp[0][i][j];
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // for (int i = 0; i < r; ++ i) {
    //     for (int j = 0; j < c; ++ j) {
    //         cout << mp[1][i][j];
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // outside
    for (int i = 0; i < r; ++ i) {
        if (mp[0][i][0] == '.') {
            dfs(i, 0, 0);
        }
        if (mp[0][i][c - 1] == '.') {
            dfs(i, c - 1, 0);
        }
        if (mp[1][i][0] == '.') {
            dfs(i, 0, 1);
        }
        if (mp[1][i][c - 1] == '.') {
            dfs(i, c - 1, 1);
        }
    }
    for (int j = 0; j < c; ++ j) {
        if (mp[0][0][j] == '.') {
            dfs(0, j, 0);
        }
        if (mp[0][r - 1][j] == '.') {
            dfs(r - 1, j, 0);
        }
        if (mp[1][0][j] == '.') {
            dfs(0, j, 1);
        }
        if (mp[1][r - 1][j] == '.') { 
            dfs(r - 1, j, 1);
        }
    }
    // inside

    for (int i = 0; i < r; ++ i) {
        for (int j = 0; j < c; ++ j) {
            if (mp[0][i][j] == '.') {
                mp[0][i][j] = 'I';
                statusRing[0][i][j] = 0;
            } else if (mp[0][i][j] == 'A') {
                statusRing[0][i][j] = 1;
            } else {
                statusRing[0][i][j] = -1;
            }
            if (mp[1][i][j] == '.') {
                mp[1][i][j] = 'I';
                statusRing[1][i][j] = 0;
            } else if (mp[1][i][j] == 'B') {
                statusRing[1][i][j] = 1;
            } else {
                statusRing[1][i][j] = -1;
            }
        }
    }
    // for (int i = 0; i < r; ++ i) {
    //     for (int j = 0; j < c; ++ j) {
    //         cout << mp[0][i][j];
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // for (int i = 0; i < r; ++ i) {
    //     for (int j = 0; j < c; ++ j) {
    //         cout << mp[1][i][j];
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    int A = 0, B = 0, AB = 0;
    for (int i = 0; i < r; ++ i) {
        for (int j = 0; j < c; ++ j) {
            if (statusRing[0][i][j] == -1 && statusRing[1][i][j] == 0) {
                ++ B;
            } else if (statusRing[0][i][j] == 0 && statusRing[1][i][j] == -1) {
                ++ A;
            } else if (statusRing[0][i][j] == 0 && statusRing[1][i][j] == 0) {
                ++ AB;
            }
        }
    }
    printf("%d %d %d\n", A, B, AB);
    return 0;
}
