#include <bits/stdc++.h>
#include "aoc.h"

#define all(x) (x).begin(), (x).end()

using namespace std;

inline int nxt() {
	int x;
	cin >> x;
	return x;
}

int main() {
	vector<int> a[2];
	int x;
	int i = 0;
	while (cin >> x) {
		a[i].push_back(x);
		i ^= 1;
	}
	sort(all(a[0]));
	sort(all(a[1]));
	map<int, int> M;
	for (int x : a[1]) {
		M[x] += 1;
	}
	long long ans = 0;
	for (int x : a[0]) {
		ans += 1ll * x * M[x];
	}
	cout << ans << "\n";

	return 0;
}
