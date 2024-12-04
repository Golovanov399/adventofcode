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

const string pat = "XMAS";
int main() {
	vector<string> a;
	{
		string s;
		while (cin >> s) {
			a.push_back(s);
		}
	}
	int ans = 0;
	for (int i = 0; i < (int)a.size(); ++i) {
		for (int j = 0; j < (int)a.size(); ++j) {
			for (int dx = -1; dx <= 1; ++dx) {
				for (int dy = -1; dy <= 1; ++dy) {
					if (!dx && !dy) {
						continue;
					}
					bool ok = true;
					for (int idx = 0; idx < (int)pat.size(); ++idx) {
						int x = i + dx * idx, y = j + dy * idx;
						if (clamp(x, 0, (int)a.size() - 1) != x || clamp(y, 0, (int)a[x].size() - 1) != y) {
							ok = false;
							continue;
						}
						ok &= a[x][y] == pat[idx];
					}
					ans += ok;
				}
			}
		}
	}
	cout << ans << "\n";

	return 0;
}
