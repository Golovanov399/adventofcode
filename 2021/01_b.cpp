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
	int cnt = 0;
	int last[3];
	fill(last, last + 3, 1e9);
	int x;
	int i = 0;
	while (cin >> x) {
		cnt += x > last[i];
		last[i] = x;
		i = (i + 1) % 3;
	}
	cout << cnt << "\n";

	return 0;
}
