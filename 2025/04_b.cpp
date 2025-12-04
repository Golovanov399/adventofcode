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
		vector<pair<int, int>> res;
		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				if (!i && !j) {
					continue;
				}
				int nx = x + i, ny = y + j;
				if (clamp(nx, 0, n - 1) == nx && clamp(ny, 0, m - 1) == ny) {
					if (a[nx][ny] == '@') {
						res.push_back({nx, ny});
					}
				}
			}
		}
		return res;
	};

	set<pair<int, pair<int, int>>> S;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (a[i][j] == '@') {
				S.insert({(int)neigs(i, j).size(), {i, j}});
			}
		}
	}

	int ans = 0;
	while (!S.empty()) {
		auto [cnt, p] = *S.begin();
		auto [x, y] = p;
		S.erase(S.begin());
		if (cnt >= 4) {
			break;
		}
		++ans;
		auto ns = neigs(x, y);
		a[x][y] = '.';
		for (auto [xx, yy] : ns) {
			int ncnt = neigs(xx, yy).size();
			S.erase({ncnt + 1, {xx, yy}});
			S.insert({ncnt, {xx, yy}});
		}
	}
	cout << ans << "\n";

	return 0;
}
