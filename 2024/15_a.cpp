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
	string s;
	while (getline(cin, s)) {
		if (s == "") {
			break;
		}
		a.push_back(s);
	}
	const int n = a.size(), m = a[0].size();
	cin >> s;
	{
		string t;
		while (cin >> t) {
			s += t;
		}
	}
	for (char d : s) {
		int x = 0, y = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (a[i][j] == '@') {
					x = i, y = j;
					break;
				}
			}
		}
		int dx = 0, dy = 0;
		if (d == '<') {
			dy = -1;
		} else if (d == '>') {
			dy = 1;
		} else if (d == '^') {
			dx = -1;
		} else if (d == 'v') {
			dx = 1;
		} else {
			assert(false);
		}
		int nx = x, ny = y;
		while (a[nx][ny] != '.' && a[nx][ny] != '#') {
			nx += dx;
			ny += dy;
		}
		if (a[nx][ny] == '.') {
			while (nx != x || ny != y) {
				swap(a[nx][ny], a[nx - dx][ny - dy]);
				nx -= dx;
				ny -= dy;
			}
		}
	}
	// for (auto s : a) {
	// 	cout << s << "\n";
	// }
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (a[i][j] == 'O') {
				ans += 100 * i + j;
			}
		}
	}
	cout << ans << "\n";

	return 0;
}
