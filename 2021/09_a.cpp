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
	vector<string> a;
	{
		string s;
		while (cin >> s) {
			a.push_back(s);
		}
	}
	const int n = a.size(), m = a[0].size();
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			bool ok = true;
			for (int dx = -1; dx <= 1; ++dx) {
				for (int dy = -1; dy <= 1; ++dy) {
					if (abs(dx) + abs(dy) != 1) {
						continue;
					}
					int x = i + dx, y = j + dy;
					if (clamp(x, 0, n - 1) != x || clamp(y, 0, m - 1) != y) {
						continue;
					}
					ok &= a[i][j] < a[x][y];
				}
			}
			if (ok) {
				ans += a[i][j] - '0' + 1;
			}
		}
	}
	cout << ans << "\n";

	return 0;
}
