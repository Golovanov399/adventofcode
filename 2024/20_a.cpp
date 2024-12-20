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
	const int n = a.size();
	const int m = a[0].size();

	pair<int, int> st = {-1, -1}, fi = {-1, -1};
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (a[i][j] == 'S') {
				st = {i, j};
				a[i][j] = '.';
			} else if (a[i][j] == 'E') {
				fi = {i, j};
				a[i][j] = '.';
			}
		}
	}

	vector<vector<int>> idx(n, vector<int>(m, -1));
	int sz = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (a[i][j] == '.') {
				idx[i][j] = sz++;
			}
		}
	}
	vector<vector<int>> g(sz);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (a[i][j] == '.') {
				if (i + 1 < n && a[i + 1][j] == '.') {
					g[idx[i][j]].push_back(idx[i + 1][j]);
					g[idx[i + 1][j]].push_back(idx[i][j]);
				}
				if (j + 1 < m && a[i][j + 1] == '.') {
					g[idx[i][j]].push_back(idx[i][j + 1]);
					g[idx[i][j + 1]].push_back(idx[i][j]);
				}
			}
		}
	}
	
	auto find_d = [&](int v) {
		vector<int> d(sz, -1);
		queue<int> q;
		q.push(v);
		d[v] = 0;
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (int x : g[v]) {
				if (d[x] == -1) {
					d[x] = d[v] + 1;
					q.push(x);
				}
			}
		}
		return d;
	};
	auto d_s = find_d(idx[st.first][st.second]);
	auto d_f = find_d(idx[fi.first][fi.second]);

	map<pair<int, int>, int> M;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (a[i][j] == '.') {
				continue;
			}
			vector<int> near;
			if (i > 0 && a[i - 1][j] == '.') {
				near.push_back(idx[i - 1][j]);
			}
			if (i < n - 1 && a[i + 1][j] == '.') {
				near.push_back(idx[i + 1][j]);
			}
			if (j > 0 && a[i][j - 1] == '.') {
				near.push_back(idx[i][j - 1]);
			}
			if (j < m - 1 && a[i][j + 1] == '.') {
				near.push_back(idx[i][j + 1]);
			}
			for (int u : near) {
				for (int v : near) {
					if (u != v) {
						M[{u, v}] = d_s[u] + d_f[v] + 2;
					}
				}
			}
		}
	}
	const int honest = d_s[idx[fi.first][fi.second]];
	map<int, int> save_by;
	int ans = 0;
	for (auto p : M) {
		ans += honest - p.second >= 100;
	}
	cout << ans << "\n";

	// for (auto p : M) {
	// 	save_by[honest - p.second] += 1;
	// }
	// for (auto [k, v] : save_by) {
	// 	if (k > 0) {
	// 		cerr << k << ": x" << v << "\n";
	// 	}
	// }

	return 0;
}
