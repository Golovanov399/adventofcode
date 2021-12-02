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
	int hor = 0, aim = 0, dep = 0;
	string s;
	int t;
	while (cin >> s >> t) {
		if (s[0] == 'f') {
			hor += t;
			dep += aim * t;
		} else if (s[0] == 'd') {
			aim += t;
		} else {
			aim -= t;
		}
	}
	cout << 1ll * hor * dep << "\n";

	return 0;
}
