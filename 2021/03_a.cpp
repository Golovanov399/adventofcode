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
	int a[2][100];
	memset(a, 0, sizeof(a));
	string s;
	int n;
	while (cin >> s) {
		n = s.length();
		for (int i = 0; i < n; ++i) {
			a[s[i] - '0'][i] += 1;
		}
	}
	int fst = 0, snd = 0;
	for (int i = 0; i < n; ++i) {
		fst = fst * 2 + (a[1][i] > a[0][i]);
		snd = snd * 2 + (a[1][i] < a[0][i]);
	}
	cout << fst * snd << "\n";

	return 0;
}
