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

bool ok(string s) {
	make_unique(s);
	return s.size() == 14;
}

int main() {
	string s;
	cin >> s;
	int i = 0;
	while (!ok(s.substr(i, 14))) {
		++i;
	}
	cout << i + 14 << "\n";

	return 0;
}
