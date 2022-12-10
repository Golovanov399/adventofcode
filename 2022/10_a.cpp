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
	int s = 0;
	int cur = 1;
	int c = 0;
	string type;
	while (cin >> type) {
		if (type == "noop") {
			if (c % 40 == 19) {
				s += cur * (c + 1);
			}
			c += 1;
		} else {
			if (c % 40 == 19) {
				s += cur * (c + 1);
			}
			c += 1;
			if (c % 40 == 19) {
				s += cur * (c + 1);
			}
			c += 1;
			cur += nxt();
		}
	}
	cout << s << "\n";

	return 0;
}
