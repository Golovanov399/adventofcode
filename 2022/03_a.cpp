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

int main() {
	string s;
	int ans = 0;
	while (cin >> s) {
		int n = s.length();
		set<int> S;
		for (int i = 0; i < n / 2; ++i) {
			S.insert(f(s[i]));
		}
		set<int> T;
		for (int i = n / 2; i < n; ++i) {
			if (S.contains(f(s[i]))) {
				T.insert(f(s[i]));
			}
		}
		for (int x : T) {
			ans += x;
		}
	}
	cout << ans << "\n";

	return 0;
}
