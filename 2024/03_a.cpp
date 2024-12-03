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
	long long ans = 0;
	string s;
	while (cin >> s) {
		for (int i = 0; i < (int)s.length(); ++i) {
			if (s.substr(i, 4) != "mul(") {
				continue;
			}
			i += 4;
			int len = s.substr(i).find(',');
			if (len == (int)string::npos) {
				continue;
			}
			int x = 0;
			int j = i + len;
			bool ok = true;
			while (i < j) {
				if (!isdigit(s[i])) {
					ok = false;
					break;
				}
				x = x * 10 + (s[i] - '0');
				i += 1;
			}
			if (!ok) {
				continue;
			}
			i += 1;
			len = s.substr(i).find(')');
			if (len == (int)string::npos) {
				continue;
			}
			int y = 0;
			j = i + len;
			while (i < j) {
				if (!isdigit(s[i])) {
					ok = false;
					break;
				}
				y = y * 10 + (s[i] - '0');
				i += 1;
			}
			if (!ok) {
				continue;
			}
			ans += x * y;
		}
	}
	cout << ans << "\n";

	return 0;
}
