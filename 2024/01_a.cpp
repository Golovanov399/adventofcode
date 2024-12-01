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
	int ans = 0;
	for (int i = 0; i < (int)a[0].size(); ++i) {
		ans += abs(a[0][i] - a[1][i]);
	}
	cout << ans << "\n";

	return 0;
}
