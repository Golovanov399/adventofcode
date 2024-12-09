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

bool rec(long long val, const vector<long long>& rhs, int i) {
	i -= 1;
	if (i == 0) {
		return val == rhs[0];
	}
	assert(rhs[i] > 0);
	if (rec(val - rhs[i], rhs, i)) {
		return true;
	}
	if (val < 0) {
		return false;
	}
	if (val % rhs[i] == 0 && rec(val / rhs[i], rhs, i)) {
		return true;
	}
	string s = to_string(val);
	string t = to_string(rhs[i]);
	if (val < rhs[i]) {
		return false;
	}
	if (s.length() > t.length() && s.substr(s.length() - t.length()) == t) {
		return rec(stoll(s.substr(0, s.length() - t.length())), rhs, i);
	} 
	return false;
}

int main() {
	string s;
	cin >> s;
	vector<int> res;
	for (int i = 0; i < (int)s.size(); i += 2) {
		if (i) {
			for (int j = 0; j < s[i - 1] - '0'; ++j) {
				res.push_back(-1);
			}
		}
		for (int j = 0; j < s[i] - '0'; ++j) {
			res.push_back(i / 2);
		}
	}
	for (int i = 0; i < (int)res.size(); ++i) {
		if (res[i] > -1) {
			continue;
		}
		res[i] = res.back();
		res.pop_back();
		while (res.back() == -1) {
			res.pop_back();
		}
	}
	long long ans = 0;
	for (int i = 0; i < (int)res.size(); ++i) {
		ans += 1ll * i * res[i];
	}
	cout << ans << "\n";

	return 0;
}
