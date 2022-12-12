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
	int n = a.size();
	int m = a[0].size();

	vector<vector<int>> d(n, vector<int>(m, 1e9));
	queue<pair<int, int>> q;
	pair<int, int> need;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (a[i][j] == 'S') {
				q.push({i, j});
				a[i][j] = 'a';
				d[i][j] = 0;
			} else if (a[i][j] == 'E') {
				need = {i, j};
				a[i][j] = 'z';
			}
		}
	}
	while (!q.empty()) {
		auto [x, y] = q.front();
		q.pop();
		for (int dx = -1; dx <= 1; ++dx) {
			for (int dy = -1; dy <= 1; ++dy) {
				if (abs(dx) + abs(dy) != 1) {
					continue;
				}
				int nx = x + dx, ny = y + dy;
				if (clamp(nx, 0, n - 1) != nx || clamp(ny, 0, m - 1) != ny) {
					continue;
				}
				if (d[nx][ny] <= d[x][y] + 1) {
					continue;
				}
				if (a[nx][ny] > a[x][y] + 1) {
					continue;
				}
				d[nx][ny] = d[x][y] + 1;
				q.push({nx, ny});
			}
		}
	}
	cout << d[need.first][need.second] << "\n";

	return 0;
}
