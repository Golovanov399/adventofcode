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

using State = array<int, 5>;


int main() {
	vector<State> a[2];
	{
		string s;
		while (cin >> s) {
			assert(s == "....." || s == "#####");
			int idx = s == "#####";
			State res = {0};
			for (int i = 0; i < 5; ++i) {
				cin >> s;
				for (int j = 0; j < 5; ++j) {
					res[j] += s[j] == '#';
				}
			}
			a[idx].push_back(res);
			cin >> s;
			assert(s == (idx ? "....." : "#####"));
		}
	}
	const int n = a[0].size(), m = a[1].size();
	vector<vector<int>> ar(n);
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			bool ok = true;
			for (int k = 0; k < 5; ++k) {
				ok &= (a[0][i][k] + a[1][j][k] <= 5);
			}
			if (ok) {
				++ans;
			}
		}
	}
	cout << ans << "\n";

	return 0;
}
