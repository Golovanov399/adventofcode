#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define itn int
#define make_unique(x) sort((x).begin(), (x).end()); (x).erase(unique((x).begin(), (x).end()), (x).end())

using namespace std;

inline int nxt() {
	int x;
	scanf("%d", &x);
	return x;
}

int main() {
	int dx = 1, dy = 0;
	int x = 0, y = 0;
	string s;
	while (cin >> s) {
		char c = s[0];
		int d = stoi(s.substr(1));
		if (c == 'L') {
			assert(d % 90 == 0);
			while (d) {
				int nx = -dy, ny = dx;
				dx = nx, dy = ny;
				d -= 90;
			}
		} else if (c == 'R') {
			assert(d % 90 == 0);
			while (d) {
				int nx = dy, ny = -dx;
				dx = nx, dy = ny;
				d -= 90;
			}
		} else if (c == 'F') {
			x += dx * d;
			y += dy * d;
		} else if (c == 'N') {
			y += d;
		} else if (c == 'S') {
			y -= d;
		} else if (c == 'E') {
			x += d;
		} else if (c == 'W') {
			x -= d;
		} else {
			assert(false);
		}
	}
	cout << abs(x) + abs(y) << "\n";

	return 0;
}
