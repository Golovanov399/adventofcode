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

int parse(string s) {
	int ans = 0;
	for (char c : s) {
		ans |= 1 << (c - 'a');
	}
	return ans;
}

int main() {
	int ans = 0;
	for (int it = 0; it < 200; ++it) {
		vector<vector<int>> ds(8);
		for (int i = 0; i < 10; ++i) {
			string s;
			cin >> s;
			ds[s.length()].push_back(parse(s));
		}
		vector<int> enc(10, -1);
		enc[1] = ds[2][0];
		enc[7] = ds[3][0];
		enc[4] = ds[4][0];
		enc[8] = ds[7][0];
		for (int x : ds[6]) {
			if ((x & enc[1]) != enc[1]) {
				enc[6] = x;
			}
		}
		for (int x : ds[5]) {
			if ((x & enc[6]) == x) {
				enc[5] = x;
			} else if ((x & enc[1]) == enc[1]) {
				enc[3] = x;
			} else {
				enc[2] = x;
			}
		}
		for (int x : ds[6]) {
			if (x == enc[6]) {
				continue;
			}
			if ((x & enc[5]) == enc[5]) {
				enc[9] = x;
			} else {
				enc[0] = x;
			}
		}
		int cur = 0;
		string s;
		cin >> s;
		for (int i = 0; i < 4; ++i) {
			cin >> s;
			cur = cur * 10 + (find(all(enc), parse(s)) - enc.begin());
		}
		ans += cur;
	}
	cout << ans << "\n";

	return 0;
}
