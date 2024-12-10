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
	const int n = a.size(), m = a[0].size();
	vector<vector<int>> dp(n, vector<int>(m, 0));
	int ans = 0;
	for (char c = '9'; c >= '0'; --c) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (a[i][j] != c) {
					continue;
				}
				if (c == '9') {
					dp[i][j] = 1;
				} else {
					for (int dx = -1; dx <= 1; ++dx) {
						for (int dy = -1; dy <= 1; ++dy) {
							if (abs(dx) + abs(dy) != 1) {
								continue;
							}
							const int x = i + dx, y = j + dy;
							if (clamp(x, 0, n - 1) == x && clamp(y, 0, m - 1) == y && a[x][y] == c + 1) {
								dp[i][j] += dp[x][y];
							}
						}
					}
				}
				if (c == '0') {
					ans += dp[i][j];
				}
			}
		}
	}
	cout << ans << "\n";

	return 0;
}
