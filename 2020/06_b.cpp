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

int main() {
	string s;
	int mask = (1 << 26) - 1;
	int ans = 0;
	while (getline(cin, s)) {
		if (s.empty()) {
			ans += __builtin_popcount(mask);
			mask = (1 << 26) - 1;
		} else {
			int tmp = 0;
			for (char c : s) {
				tmp |= 1 << (c - 'a');
			}
			mask &= tmp;
		}
	}
	cout << ans << "\n";

	return 0;
}
