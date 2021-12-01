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
	int last = 1e9;
	int cnt = 0;
	int x;
	while (cin >> x) {
		cnt += x > last;
		last = x;
	}
	cout << cnt << "\n";

	return 0;
}
