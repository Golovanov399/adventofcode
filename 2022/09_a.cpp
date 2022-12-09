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

int main() {
	Point h{0, 0}, t{0, 0};
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
			h.x += dx;
			h.y += dy;

			if (abs(t.x - h.x) <= 1 && abs(t.y - h.y) <= 1) {
				//
			} else if (t.x == h.x || t.y == h.y) {
				t.x += dx;
				t.y += dy;
			} else {
				t.x = h.x - dx;
				t.y = h.y - dy;
			}
			S.insert(t.x * 10000 + t.y);
		}
	}
	cout << S.size() << "\n";

	return 0;
}
