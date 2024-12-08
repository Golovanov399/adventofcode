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

bool rec(long long val, const vector<long long>& rhs, int i) {
	i -= 1;
	if (i == 0) {
		return val == rhs[0];
	}
	assert(rhs[i] > 0);
	if (rec(val - rhs[i], rhs, i)) {
		return true;
	}
	if (val < 0) {
		return false;
	}
	if (val % rhs[i] == 0 && rec(val / rhs[i], rhs, i)) {
		return true;
	}
	string s = to_string(val);
	string t = to_string(rhs[i]);
	if (val < rhs[i]) {
		return false;
	}
	if (s.length() > t.length() && s.substr(s.length() - t.length()) == t) {
		return rec(stoll(s.substr(0, s.length() - t.length())), rhs, i);
	} 
	return false;
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
	vector<vector<char>> used(n, vector<char>(m, false));
	map<char, vector<pair<int, int>>> M;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (a[i][j] != '.') {
				M[a[i][j]].push_back({i, j});
			}
		}
	}
	for (const auto& [_, v] : M) {
		for (const auto& [x1, y1] : v) {
			for (const auto& [x2, y2] : v) {
				if (x1 == x2 && y1 == y2) {
					continue;
				}
				int x3 = 2 * x2 - x1;
				int y3 = 2 * y2 - y1;
				if (clamp(x3, 0, n - 1) == x3 && clamp(y3, 0, m - 1) == y3) {
					used[x3][y3] = true;
				}
			}
		}
	}
	int ans = 0;
	for (auto v : used) {
		ans += count(all(v), true);
	}
	cout << ans << "\n";

	return 0;
}
