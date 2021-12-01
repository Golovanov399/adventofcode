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
	long long ans = -228;
	long long x;
	set<long long> S;
	while (cin >> x) {
		if (S.count(2020 - x)) {
			assert(ans == -228);
			ans = x * (2020 - x);
		}
		S.insert(x);
	}
	cout << ans << "\n";

	return 0;
}
