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
	int x = 0, y = 0;
	string s;
	int t;
	while (cin >> s >> t) {
		if (s[0] == 'f') {
			x += t;
		} else if (s[0] == 'd') {
			y += t;
		} else {
			y -= t;
		}
	}
	cout << x * y << "\n";

	return 0;
}
