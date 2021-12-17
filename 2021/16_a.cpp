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

void parse(const string& s) {
	int v = toint(s.substr(pos, 3));
	pos += 3;
	int t = toint(s.substr(pos, 3));
	pos += 3;
	ans += v;
	if (t == 4) {
		while (s[pos] == '1') {
			pos += 5;
		}
		pos += 5;
	} else {
		if (s[pos++] == '0') {
			int len = toint(s.substr(pos, 15));
			pos += 15;
			int when = pos + len;
			while (pos < when) {
				parse(s);
			}
		} else {
			int cnt = toint(s.substr(pos, 11));
			pos += 11;
			for (int i = 0; i < cnt; ++i) {
				parse(s);
			}
		}
	}
}

int main() {
	string s;
	cin >> s;
	s = to_bin(s);
	cerr << s << "\n";

	parse(s);
	cout << ans << "\n";

	return 0;
}
