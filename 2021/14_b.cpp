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

long long cnt1[26];
long long cnt2[26][26];

long long tmp1[26];
long long tmp2[26][26];

int main() {
	string s;
	cin >> s;

	string from, arrow, to;
	map<string, char> M;
	while (cin >> from >> arrow >> to) {
		M[from] = to[0];
	}

	for (char c : s) {
		cnt1[c - 'A'] += 1;
	}
	for (int i = 0; i < (int)s.length() - 1; ++i) {
		cnt2[s[i] - 'A'][s[i + 1] - 'A'] += 1;
	}

	for (int it = 0; it < 40; ++it) {
		memset(tmp1, 0, sizeof(tmp1));
		memset(tmp2, 0, sizeof(tmp2));
		for (auto [fr, to] : M) {
			int x = fr[0] - 'A', y = fr[1] - 'A';
			int c = to - 'A';
			long long cc = cnt2[x][y];
			tmp2[x][y] -= cc;
			tmp2[x][c] += cc;
			tmp2[c][y] += cc;
			tmp1[c] += cc;
		}
		for (int i = 0; i < 26; ++i) {
			for (int j = 0; j < 26; ++j) {
				cnt2[i][j] += tmp2[i][j];
			}
			cnt1[i] += tmp1[i];
		}
	}

	long long mn = 1e18;
	for (int i = 0; i < 26; ++i) {
		if (cnt1[i]) {
			mn = min(mn, cnt1[i]);
		}
	}
	cout << *max_element(cnt1, cnt1 + 26) - mn << "\n";

	return 0;
}
