#define _USE_MATH_DEFINES

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
	int R,C; cin >> R >> C;
	
	vector<string> maze(R);
	for (auto &row: maze) {
		cin >> row;
		row = "...." + row + "....";
	}
	C += 8;
	
	bool forwardeven = true;
	for (int i=0; i<R; ++i) {
		for (int j=0; j<C; ++j) {
			//cout << ((i+j) % 2 == 0 ? '\\' : '/');
			if (maze[i][j] == ((i+j) % 2 == 0 ? '\\' : '/')) {
				forwardeven = false;
			}
		}
	}
	
	if (!forwardeven) {
		maze.insert(maze.begin(), string(C, '.'));
		++R;
	}
	for (int i=0; i<4; ++i) {
		maze.insert(maze.begin(), string(C, '.'));
		maze.insert(maze.end(), string(C, '.'));
		R += 2;
	}
	
	int floodfill[1024][1024] = {{0}};
	
	auto inbounds = [&](int i, int j) { return i>=0 && j>=0 && i<R && j<C; };
	
	function<void(int,int,int)> f = [&](int i, int j, int v) {
		if (floodfill[i][j] != 0) return;
		floodfill[i][j] = v;
		int ip = i+1, jp = j+1;
		if (inbounds(ip,jp) && maze[ip][jp] != '/') {
			f(ip, jp, v);
		}
		ip = i+1, jp = j-1;
		if (inbounds(ip,jp) && maze[ip][j] != '\\') {
			f(ip, jp, v);
		}
		ip = i-1, jp = j+1;
		if (inbounds(ip,jp) && maze[i][jp] != '\\') {
			f(ip, jp, v);
		}
		ip = i-1, jp = j-1;
		if (inbounds(ip,jp) && maze[i][j] != '/') {
			f(ip, jp, v);
		}
	};
	
	int fillno = 1;
	for (int i=0; i<R; ++i) {
		for (int j=i%2; j<C; j+=2) {
			if (floodfill[i][j] == 0) {
				f(i, j, fillno++);
			}
		}
	}
	
#if 0
	for (int i=0; i<R; ++i) {
		for (int j=0; j<C; ++j) {
			cout << floodfill[i][j] << " ";
		}
		cout << endl;
	}
#endif
	
	cout << (fillno - 2) << endl;
	
	return 0;
}
