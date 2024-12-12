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

	auto add_side = [&](set<array<int, 4>>& S, int x, int y, int nx, int ny) {
		int dx = nx - x, dy = ny - y;
		int sx = x + nx + 1, sy = y + ny + 1;
		S.insert({sx - dy, sy - dx, sx + dy, sy + dx});
	};

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (used[i][j]) {
				continue;
			}
			vector<pair<int, int>> st = {{i, j}};
			used[i][j] = true;
			int ver = 0;
			set<array<int, 4>> sides;
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
							add_side(sides, x, y, nx, ny);
							continue;
						}
						if (a[nx][ny] != a[x][y]) {
							add_side(sides, x, y, nx, ny);
						} else if (!used[nx][ny]) {
							st.push_back({nx, ny});
							used[nx][ny] = true;
						}
					}
				}
			}

			map<pair<int, int>, pair<int, int>> M;
			map<pair<int, int>, int> cnt;
			for (auto v : sides) {
				M[{v[0], v[1]}].first += v[2];
				M[{v[0], v[1]}].second += v[3];
				M[{v[2], v[3]}].first += v[0];
				M[{v[2], v[3]}].second += v[1];
				cnt[{v[0], v[1]}] += 1;
				cnt[{v[2], v[3]}] += 1;
			}
			int per = 0;
			for (auto [k, v] : M) {
				per += v.first != k.first * 2 || v.second != k.second * 2;
				per += cnt[k] / 2 - 1;
			}
			// cerr << a[i][j] << ": " << ver << " " << per << "\n";
			ans += 1ll * ver * per;
		}
	}
	cout << ans << "\n";

	return 0;
}
