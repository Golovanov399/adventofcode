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

	map<int, long long> pos;
	for (int i = 0; i < m; ++i) {
		if (a[0][i] == 'S') {
			pos[i] = 1;
		}
	}
	for (int i = 1; i < n; ++i) {
		map<int, long long> npos;
		for (auto [j, cnt] : pos) {
			if (a[i][j] == '^') {
				npos[j - 1] += cnt;
				npos[j + 1] += cnt;
			} else {
				npos[j] += cnt;
			}
		}
		pos.swap(npos);
	}
	long long ans = 0;
	for (auto p : pos) {
		ans += p.second;
	}
	cout << ans << "\n";

	return 0;
}
