#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define itn int
#define make_unique(x) sort((x).begin(), (x).end()); (x).erase(unique((x).begin(), (x).end()), (x).end())

using namespace std;

inline int nxt() {
	int x;
	scanf("%d", &x);
	return x;
}

string to_bin(string s) {
	string t;
	for (char c : s) {
		int x = (isdigit(c)) ? c - '0' : c - 'A' + 10;
		string b = "";
		for (int i = 0; i < 4; ++i) {
			b += (char)('0' + x % 2);
			x /= 2;
		}
		reverse(all(b));
		t += b;
	}
	return t;
}

int toint(string s) {
	int res = 0;
	for (char c : s) {
		res = res * 2 + c - '0';
	}
	return res;
}

int ans = 0;
int pos = 0;

using li = long long;

const vector<function<li(li, li)>> ops = {
	[](li x, li y) { return x + y; },
	[](li x, li y) { return x * y; },
	[](li x, li y) { return min(x, y); },
	[](li x, li y) { return max(x, y); },
	[](li, li) -> li { assert(false); },
	[](li x, li y) -> li { return x > y; },
	[](li x, li y) -> li { return x < y; },
	[](li x, li y) -> li { return x == y; },
};

li parse(const string& s) {
	int v = toint(s.substr(pos, 3));
	pos += 3;
	int t = toint(s.substr(pos, 3));
	pos += 3;
	ans += v;
	if (t == 4) {
		li num = 0;
		while (s[pos] == '1') {
			num = (num << 4) | toint(s.substr(pos + 1, 4));
			pos += 5;
		}
		num = (num << 4) | toint(s.substr(pos + 1, 4));
		pos += 5;
		return num;
	} else {
		vector<li> args;
		if (s[pos++] == '0') {
			int len = toint(s.substr(pos, 15));
			pos += 15;
			int when = pos + len;
			while (pos < when) {
				args.push_back(parse(s));
			}
		} else {
			int cnt = toint(s.substr(pos, 11));
			pos += 11;
			for (int i = 0; i < cnt; ++i) {
				args.push_back(parse(s));
			}
		}
		const auto& f = ops[t];
		li res = args[0];
		for (int i = 1; i < (int)args.size(); ++i) {
			res = f(res, args[i]);
		}
		return res;
	}
}

int main() {
	string s;
	cin >> s;
	s = to_bin(s);
	cerr << s << "\n";

	cout << parse(s) << "\n";
	// cout << ans << "\n";

	return 0;
}
