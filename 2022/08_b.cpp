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

int main() {
	vector<string> a;
	{
		string s;
		while (cin >> s) {
			a.push_back(s);
		}
	}

	const int n = a.size();
	const int m = a[0].size();
	auto f = [&](int x, int y, int dx, int dy) {
		int cnt = 0;
		char thres = a[x][y];
		while (true) {
			x += dx;
			y += dy;
			if (clamp(x, 0, n - 1) == x && clamp(y, 0, m - 1) == y) {
				++cnt;
				if (a[x][y] >= thres) {
					break;
				}
			} else {
				break;
			}
		}
		return cnt;
	};

	int ans = 0;
	for (int i = 1; i < n - 1; ++i) {
		for (int j = 1; j < m - 1; ++j) {
			ans = max(ans, f(i, j, -1, 0) * f(i, j, 1, 0) * f(i, j, 0, -1) * f(i, j, 0, 1));
		}
	}
	cout << ans << "\n";

	return 0;
}
