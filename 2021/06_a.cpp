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

int a[9];

int main() {
	string s;
	cin >> s;
	for (char c : s) {
		if (c != ',') {
			++a[c - '0'];
		}
	}
	for (int i = 0; i < 81; ++i) {
		rotate(a, a + 1, a + 9);
		a[6] += a[8];
	}
	cout << accumulate(a, a + 8, 0) << "\n";

	return 0;
}
