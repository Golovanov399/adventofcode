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
	int res = 0;
	int cur = 50;
	string s;
	while (cin >> s) {
		int d = (s[0] == 'L' ? -1 : 1);
		cur += d * stoi(s.substr(1));
		cur %= 100;
		if (cur < 0) {
			cur += 100;
		}
		res += cur == 0;
	}
	cout << res << "\n";

	return 0;
}
