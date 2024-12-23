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
	map<string, set<string>> M;
	{
		string s;
		while (cin >> s) {
			int i = s.find('-');
			auto l = s.substr(0, i), r = s.substr(i + 1);
			M[l].insert(r);
			M[r].insert(l);
		}
	}

	int ans = 0;
	for (const auto& [a, s] : M) {
		for (auto b : s) {
			for (auto c : s) {
				if (a < b && a < c && b < c && M[b].contains(c) && (a[0] == 't' || b[0] == 't' || c[0] == 't')) {
					ans += 1;
				}
			}
		}
	}
	cout << ans << "\n";

	return 0;
}
