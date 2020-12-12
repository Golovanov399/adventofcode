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
	vector<int> a;
	int x;
	while (cin >> x) {
		a.push_back(x);
	}
	sort(all(a));
	int d1 = 0, d3 = 1;
	int last = 0;
	for (int x : a) {
		assert(x == last + 1 || x == last + 3);
		if (x == last + 1) {
			++d1;
		} else {
			++d3;
		}
		last = x;
	}
	cout << d1 * d3 << "\n";

	return 0;
}
