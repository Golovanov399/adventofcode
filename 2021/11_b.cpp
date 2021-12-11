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

const int n = 10;
int a[n][n];
char used[n][n];

int main() {
	for (int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		for (int j = 0; j < n; ++j) {
			a[i][j] = s[j] - '0';
		}
	}
	int ans = 0;
	for (int it = 0;; ++it) {
		int mx = 0;
		vector<pair<int, int>> st;
		memset(used, 0, sizeof(used));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				mx = max(mx, a[i][j]);
				// if (++a[i][j] > 9) {
				// 	used[i][j] = 1;
				// 	st.push_back({i, j});
				// }
			}
		}
		ans += 10 - mx;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				a[i][j] += 10 - mx;
				if (a[i][j] > 9) {
					used[i][j] = 1;
					st.push_back({i, j});
				}
			}
		}
		int cnt = 0;
		while (!st.empty()) {
			auto [x, y] = st.back();
			st.pop_back();
			a[x][y] = 0;
			++cnt;
			for (int dx : {-1, 0, 1}) {
				for (int dy : {-1, 0, 1}) {
					int nx = x + dx, ny = y + dy;
					if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
						continue;
					}
					if (used[nx][ny]) {
						continue;
					}
					if (++a[nx][ny] > 9) {
						used[nx][ny] = 1;
						st.push_back({nx, ny});
					}
				}
			}
		}
		if (cnt == n * n) {
			cout << ans << "\n";
			return 0;
		}
	}

	return 0;
}
