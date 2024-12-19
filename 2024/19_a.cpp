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
	vector<string> can;
	string s;
	getline(cin, s);
	{
		stringstream sstr(s);
		string t;
		while (sstr >> t) {
			if (t.back() == ',') {
				t.pop_back();
			}
			can.push_back(t);
		}
		sort(all(can));
	}
	int ans = 0;
	while (cin >> s) {
		const int n = s.length();
		vector<char> dp(n + 1);
		dp[0] = 1;
		for (int i = 0; i < n; ++i) {
			if (!dp[i]) {
				continue;
			}
			for (int len = 1; i + len <= n; ++len) {
				if (binary_search(all(can), s.substr(i, len))) {
					dp[i + len] = true;
				}
			}
		}
		if (dp[n]) {
			// cerr << s << "\n";
			ans += 1;
		}
	}
	cout << ans << "\n";

	return 0;
}
