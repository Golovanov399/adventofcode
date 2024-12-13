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
	int ans = 0;

	string s;
	while (cin >> s) {
		cin >> s;
		cin >> s;
		s.pop_back();
		s = s.substr(s.find('+') + 1);
		int ax = stoi(s);
		cin >> s;
		s = s.substr(s.find('+') + 1);
		int ay = stoi(s);

		cin >> s;
		cin >> s;
		cin >> s;
		s.pop_back();
		s = s.substr(s.find('+') + 1);
		int bx = stoi(s);
		cin >> s;
		s = s.substr(s.find('+') + 1);
		int by = stoi(s);

		cin >> s;
		cin >> s;
		s.pop_back();
		s = s.substr(s.find('=') + 1);
		int x = stoi(s);
		cin >> s;
		s = s.substr(s.find('=') + 1);
		int y = stoi(s);

		int res = INT_MAX;
		for (int i = 0; i <= 100; ++i) {
			int rx = x - ax * i, ry = y - ay * i;
			if (rx >= 0 && ry >= 0 && rx % bx == 0 && ry % by == 0 && rx / bx == ry / by && rx / bx <= 100) {
				res = min(res, 3 * i + (rx / bx));
			}
		}
		if (res != INT_MAX) {
			ans += res;
		}
	}
	cout << ans << "\n";

	return 0;
}
