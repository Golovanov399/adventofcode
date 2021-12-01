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
	vector<long long> mem;
	long long ones, zeroes;
	string s;
	while (getline(cin, s)) {
		if (s.empty()) {
			break;
		}
		if (s.substr(0, 4) == "mask") {
			string t = s.substr(7);
			ones = zeroes = 0;
			reverse(all(t));
			for (int i = 0; i < (int)t.size(); ++i) {
				if (t[i] == '0') {
					zeroes |= 1ll << i;
				} else if (t[i] == '1') {
					ones |= 1ll << i;
				}
			}
		} else {
			int idx = 0;
			int i = 4;
			while (isdigit(s[i])) {
				idx = idx * 10 + s[i] - '0';
				++i;
			}
			i += 4;
			long long val = stoll(s.substr(i));
			if (idx >= (int)mem.size()) {
				mem.resize(idx + 1);
			}
			val |= ones;
			val &= ~zeroes;
			mem[idx] = val;
		}
	}
	cout << accumulate(all(mem), 0ll) << "\n";

	return 0;
}
