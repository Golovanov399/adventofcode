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
	const string s = "253149867";
	const int n = s.length();
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		a[i] = s[i] - '0';
	}
	for (int i = 0; i < 100; ++i) {
		int cur = a[0];
		rotate(a.begin(), 1 + all(a));
		vector<int> b(a.begin(), a.begin() + 3);
		a.erase(a.begin(), a.begin() + 3);
		while (true) {
			--cur;
			if (cur < 0) {
				cur = *max_element(all(a));
			}
			auto it = find(all(a), cur);
			if (it != a.end()) {
				a.insert(next(it), all(b));
				break;
			}
		}
	}
	auto it = find(all(a), 1);
	rotate(a.begin(), it, a.end());
	a.erase(a.begin());
	for (auto x : a) {
		cout << x;
	}
	cout << "\n";

	return 0;
}
