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
	vector<vector<char>> used(n, vector<char>(m, 0));
	vector<int> cnts;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (a[i][j] == '9' || used[i][j]) {
				continue;
			}
			vector<pair<int, int>> st = {{i, j}};
			used[i][j] = true;
			int cnt = 0;
			while (!st.empty()) {
				auto [x, y] = st.back();
				st.pop_back();
				++cnt;
				for (int dx = -1; dx <= 1; ++dx) {
					for (int dy = -1; dy <= 1; ++dy) {
						if (abs(dx) + abs(dy) != 1) {
							continue;
						}
						int nx = x + dx, ny = y + dy;
						if (clamp(nx, 0, n - 1) != nx || clamp(ny, 0, m - 1) != ny) {
							continue;
						}
						if (used[nx][ny] || a[nx][ny] == '9') {
							continue;
						}
						used[nx][ny] = 1;
						st.push_back({nx, ny});
					}
				}
			}
			cnts.push_back(cnt);
		}
	}
	sort(all(cnts));
	reverse(all(cnts));
	cout << cnts[0] * cnts[1] * cnts[2] << "\n";

	return 0;
}
