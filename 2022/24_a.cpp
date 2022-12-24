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

bool starts_with(string s, string t) {
	return s.length() >= t.length() && s.substr(0, t.length()) == t;
}

vector<string> split(string s, string by = " ") {
	vector<string> res = {""};
	for (int i = 0; i < (int)s.length(); ++i) {
		if (s.substr(i, by.length()) == by) {
			res.push_back("");
			i += (int)by.length() - 1;
		} else {
			res.back() += s[i];
		}
	}
	return res;
}

int true_mod(int x, int y) {
	return ((x % y) + y) % y;
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

	auto is_occupied = [&](int i, int j, int t) {
		if (clamp(i, 0, n - 1) != i || clamp(j, 0, m - 1) != j) {
			return true;
		}
		if (a[i][j] == '#') {
			return true;
		}
		if (i == 0 || i == n - 1) {
			return false;
		}
		if (a[i][true_mod(j - t - 1, m - 2) + 1] == '>') {
			return true;
		}
		if (a[i][true_mod(j + t - 1, m - 2) + 1] == '<') {
			return true;
		}
		if (a[true_mod(i - t - 1, n - 2) + 1][j] == 'v') {
			return true;
		}
		if (a[true_mod(i + t - 1, n - 2) + 1][j] == '^') {
			return true;
		}
		return false;
	};

	vector<pair<int, int>> where = {{0, 1}};
	int t = 0;
	while (true) {
		++t;
		vector<pair<int, int>> new_where;
		for (auto [x, y] : where) {
			for (int dx = -1; dx <= 1; ++dx) {
				for (int dy = -1; dy <= 1; ++dy) {
					if (abs(dx) + abs(dy) > 1) {
						continue;
					}
					int nx = x + dx, ny = y + dy;
					if (!is_occupied(nx, ny, t)) {
						new_where.push_back({nx, ny});
					}
				}
			}
		}
		make_unique(new_where);
		// vector<string> b(n, string(m, '.'));
		// for (int i = 0; i < n; ++i) {
		// 	for (int j = 0; j < m; ++j) {
		// 		if (is_occupied(i, j, t)) {
		// 			b[i][j] = '#';
		// 		}
		// 	}
		// }
		// for (auto [x, y] : new_where) {
		// 	assert(b[x][y] != '#');
		// 	b[x][y] = '?';
		// }
		// for (auto s : b) {
		// 	cerr << s << "\n";
		// }
		// cerr << "\n";
		if (new_where.back() == pair{n - 1, m - 2}) {
			break;
		}
		new_where.swap(where);
	}
	cout << t << "\n";

	return 0;
}
