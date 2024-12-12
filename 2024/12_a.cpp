#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()

using namespace std;

inline int nxt() {
	int x;
	cin >> x;
	return x;
}

vector<int> read_ints() {
	vector<int> res;
	int x;
	while (cin >> x) {
		res.push_back(x);
	}
	return res;
}

vector<int> read_ints(const string& s) {
	stringstream sstr(s);
	vector<int> res;
	int x;
	while (sstr >> x) {
		res.push_back(x);
	}
	return res;
}

string read_line() {
	string s;
	getline(cin, s);
	return s;
}

vector<string> read_lines() {
	vector<string> res;
	string s;
	while (getline(cin, s)) {
		res.push_back(s);
	}
	return res;
}

int main() {
	vector<string> a;
	{
		string s;
		while (cin >> s) {
			a.push_back(s);
		}
	}
	long long ans = 0;
	const int n = a.size();
	const int m = a[0].size();
	vector<vector<char>> used(n, vector<char>(m, 0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (used[i][j]) {
				continue;
			}
			vector<pair<int, int>> st = {{i, j}};
			used[i][j] = true;
			int ver = 0;
			int ed = 0;
			while (!st.empty()) {
				auto [x, y] = st.back();
				st.pop_back();
				ver += 1;
				for (int dx = -1; dx <= 1; ++dx) {
					for (int dy = -1; dy <= 1; ++dy) {
						if (abs(dx) + abs(dy) != 1) {
							continue;
						}
						int nx = x + dx, ny = y + dy;
						if (clamp(nx, 0, n - 1) != nx || clamp(ny, 0, m - 1) != ny) {
							continue;
						}
						if (a[nx][ny] != a[x][y]) {
							continue;
						}
						++ed;
						if (!used[nx][ny]) {
							st.push_back({nx, ny});
							used[nx][ny] = true;
						}
					}
				}
			}

			int per = 4 * ver - ed;
			ans += 1ll * ver * per;
		}
	}
	cout << ans << "\n";

	return 0;
}
