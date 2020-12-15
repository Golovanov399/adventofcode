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
	map<long long, int> mem;
	long long ones, xs;
	string s;
	while (getline(cin, s)) {
		if (s.empty()) {
			break;
		}
		if (s.substr(0, 4) == "mask") {
			string t = s.substr(7);
			ones = xs = 0;
			reverse(all(t));
			for (int i = 0; i < (int)t.size(); ++i) {
				if (t[i] == 'X') {
					xs |= 1ll << i;
				} else if (t[i] == '1') {
					ones |= 1ll << i;
				}
			}
		} else {
			long long idx = 0;
			int i = 4;
			while (isdigit(s[i])) {
				idx = idx * 10 + s[i] - '0';
				++i;
			}
			i += 4;
			long long val = stoll(s.substr(i));
			idx |= ones;
			idx &= ~xs;
			for (long long mask = xs; mask >= 0; mask = (mask - 1) & xs) {
				mem[idx | mask] = val;
				if (!mask) {
					break;
				}
			}
		}
	}
	long long ans = 0;
	for (auto p : mem) {
		ans += p.second;
	}
	cout << ans << "\n";

	return 0;
}
