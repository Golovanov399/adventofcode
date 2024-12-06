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
	vector<vector<char>> used(n, vector<char>(m, false));
	int x = -1, y = -1;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (a[i][j] == '^') {
				x = i, y = j;
			}
		}
	}
	int dx = -1, dy = 0;
	int ans = 0;
	while (clamp(x, 0, n - 1) == x && clamp(y, 0, m - 1) == y) {
		ans += 1 - used[x][y];
		used[x][y] = true;
		int nx = x + dx, ny = y + dy;
		if (clamp(nx, 0, n - 1) == nx && clamp(ny, 0, m - 1) == ny && a[nx][ny] == '#') {
			dx *= -1;
			swap(dx, dy);
		} else {
			x = nx, y = ny;
		}
	}
	cout << ans << "\n";

	return 0;
}
