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

int get_max(string s) {
	char mx = 0;
	int ans = 0;
	for (int i = (int)s.length() - 1; i >= 0; --i) {
		if (mx) {
			ans = max(ans, (s[i] - '0') * 10 + (mx - '0'));
		}
		mx = max(mx, s[i]);
	}
	return ans;
}

int main() {
	auto lines = read_lines();
	int ans = 0;
	for (auto s : lines) {
		ans += get_max(s);
	}
	cout << ans << "\n";

	return 0;
}
