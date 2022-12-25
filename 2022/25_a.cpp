#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define itn int
#define make_unique(x) sort((x).begin(), (x).end()); (x).erase(unique((x).begin(), (x).end()), (x).end())

using namespace std;

inline int nxt() {
	int x;
	cin >> x;
	return x;
}

bool starts_with(string s, string t) {
	return s.length() >= t.length() && s.substr(0, t.length()) == t;
}

vector<string> split(string s, string by = " ") {
	vector<string> res = {""};
	for (int i = 0; i < (int)s.length(); ++i) {
		if (s.substr(i, by.length()) == by) {
			res.push_back("");
			i += (int)by.length() - 1;
		} else {
			res.back() += s[i];
		}
	}
	return res;
}

int snafu_digit_to_dec(char c) {
	if (c == '=') {
		return -2;
	} else if (c == '-') {
		return -1;
	} else {
		return c - '0';
	}
}

long long snafu_to_normal(const string& s) {
	long long ans = 0;
	for (char c : s) {
		ans = ans * 5 + snafu_digit_to_dec(c);
	}
	return ans;
}

string normal_to_snafu(long long x) {
	long long p = 1;
	while (abs(x) > (p - 1) / 2) {
		p *= 5;
	}
	for (long long i = 1; i < p; i *= 5) {
		x += i * 2;
	}
	string ans;
	while (p > 1) {
		p /= 5;
		ans += "=-012"[x / p];
		x %= p;
	}
	if (ans.empty()) {
		ans += '0';
	}
	return ans;
}

int main() {
	long long ans = 0;
	{
		string s;
		while (cin >> s) {
			ans += snafu_to_normal(s);
		}
	}
	cout << normal_to_snafu(ans) << "\n";

	return 0;
}
