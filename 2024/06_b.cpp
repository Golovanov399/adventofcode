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
	const int n = a.size(), m = a[0].size();
	vector<int> used(4 * n * m);
	int timer = 0;
	int x = -1, y = -1;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (a[i][j] == '^') {
				x = i, y = j;
			}
		}
	}
	pair<int, int> st(x, y);
	int dx = -1, dy = 0;
	vector<pair<int, int>> cands;
	while (clamp(x, 0, n - 1) == x && clamp(y, 0, m - 1) == y) {
		int nx = x + dx, ny = y + dy;
		if (clamp(nx, 0, n - 1) == nx && clamp(ny, 0, m - 1) == ny && a[nx][ny] != '#') {
			cands.push_back({nx, ny});
		}
		if (clamp(nx, 0, n - 1) == nx && clamp(ny, 0, m - 1) == ny && a[nx][ny] == '#') {
			dx *= -1;
			swap(dx, dy);
		} else {
			x = nx, y = ny;
		}
	}
	sort(all(cands));
	cands.resize(unique(all(cands)) - cands.begin());

	auto is_in_loop = [&](int xx, int yy) {
		auto [x, y] = st;
		int dx = -1, dy = 0;
		++timer;
		while (clamp(x, 0, n - 1) == x && clamp(y, 0, m - 1) == y) {
			const int idx = (x * m + y) * 4 + (dx == -1 ? 0 : dy == -1 ? 1 : dy == 1 ? 2 : 3);
			if (used[idx] == timer) {
				return true;
			}
			used[idx] = timer;
			int nx = x + dx, ny = y + dy;
			if (clamp(nx, 0, n - 1) == nx && clamp(ny, 0, m - 1) == ny && (a[nx][ny] == '#' || (nx == xx && ny == yy))) {
				dx *= -1;
				swap(dx, dy);
			} else {
				x = nx, y = ny;
			}
		}
		return false;
	};
	int ans = 0;
	for (auto [xx, yy] : cands) {
		ans += is_in_loop(xx, yy);
	}
	cout << ans << "\n";

	return 0;
}
