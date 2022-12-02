#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define itn int
#define make_unique(x) sort((x).begin(), (x).end()); (x).erase(unique((x).begin(), (x).end()), (x).end())

using namespace std;

inline int nxt() {
	int x;
	cin >> x;
	return x;
}

int main() {
	char a, x;
	int ans = 0;
	while (cin >> a >> x) {
		int aa = a - 'A';
		int xx = x - 'X';
		int out = -1;
		while ((aa + out + 3) % 3 != xx) {
			++out;
		}
		ans += 1 + xx + (1 + out) * 3;
	}
	cout << ans << "\n";

	return 0;
}
