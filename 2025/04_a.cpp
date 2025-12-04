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
	auto a = read_lines();
	const int n = a.size();
	const int m = a[0].size();

	auto neigs = [&](int x, int y) {
		int ans = 0;
		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				if (!i && !j) {
					continue;
				}
				int nx = x + i, ny = y + j;
				if (clamp(nx, 0, n - 1) == nx && clamp(ny, 0, m - 1) == ny) {
					ans += a[nx][ny] == '@';
				}
			}
		}
		return ans;
	};

	int ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			ans += (a[i][j] == '@' && neigs(i, j) < 4);
		}
	}
	cout << ans << "\n";

	return 0;
}
