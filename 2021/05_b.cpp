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

const int N = 1000;
int a[N][N];

pair<int, int> parse(string s) {
	int idx = s.find(',');
	return {stoi(s.substr(0, idx)), stoi(s.substr(idx + 1))};
}

int main() {
	for (int i = 0; i < 500; ++i) {
		string s, t;
		cin >> s >> t;
		cin >> t;
		auto [x1, y1] = parse(s);
		auto [x2, y2] = parse(t);
		int dx = x2 < x1 ? -1 : x2 > x1;
		int dy = y2 < y1 ? -1 : y2 > y1;
		if (abs(dx) > 1 || abs(dy) > 1) {
			continue;
		}
		int x = x1, y = y1;
		while (true) {
			a[x][y] += 1;
			if (x == x2 && y == y2) {
				break;
			}
			x += dx;
			y += dy;
		}
	}
	int ans = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			ans += a[i][j] > 1;
		}
	}
	cout << ans << "\n";

	return 0;
}
