#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define itn int
#define make_unique(x) sort((x).begin(), (x).end()); (x).erase(unique((x).begin(), (x).end()), (x).end())

using namespace std;

inline int nxt() {
	int x;
	cin >> x;
	return x;
}

struct Point {
	int x, y;
};

int sign(int x) {
	return x < 0 ? -1 : x > 0;
}

int main() {
	vector<Point> rope(10, Point{0, 0});
	char dir;
	int s;
	set<int> S;
	S.insert(0);
	while (cin >> dir >> s) {
		int dx = 0, dy = 0;
		if (dir == 'L') {
			dx -= 1;
		} else if (dir == 'R') {
			dx += 1;
		} else if (dir == 'U') {
			dy += 1;
		} else {
			dy -= 1;
		}
		while (s--) {
			rope[0].x += dx, rope[0].y += dy;

			for (int i = 0; i < 9; ++i) {
				int sx = 0, sy = 0;
				if (abs(rope[i + 1].x - rope[i].x) <= 1 && abs(rope[i + 1].y - rope[i].y) <= 1) {
					//
				} else if ((dx == 0 && rope[i + 1].x == rope[i].x) || (dy == 0 && rope[i + 1].y == rope[i].y)) {
					sx = dx;
					sy = dy;
				} else {
					sx = sign(rope[i].x - rope[i + 1].x);
					sy = sign(rope[i].y - rope[i + 1].y);
				}
				rope[i + 1].x += sx;
				rope[i + 1].y += sy;
			}
			S.insert(rope[9].x * 10000 + rope[9].y);
		}
	}
	cout << S.size() << "\n";

	return 0;
}
