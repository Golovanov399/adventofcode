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

int f(char c) {
	if (clamp(c, 'a', 'z') == c) {
		return c - 'a' + 1;
	} else {
		return c - 'A' + 27;
	}
}

long long g(string s) {
	long long res = 0;
	for (char c : s) {
		res |= 1ll << f(c);
	}
	return res;
}

int main() {
	string s;
	int ans = 0;
	while (cin >> s) {
		auto m = g(s);
		cin >> s;
		m &= g(s);
		cin >> s;
		m &= g(s);
		ans += __builtin_ctzll(m);
	}
	cout << ans << "\n";

	return 0;
}
