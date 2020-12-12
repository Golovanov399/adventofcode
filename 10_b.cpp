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
	a.push_back(0);
	sort(all(a));
	vector<long long> cnt(a.size());
	cnt[0] = 1;
	for (int i = 1; i < (int)a.size(); ++i) {
		for (int j = i - 1; j >= 0 && a[i] - a[j] <= 3; --j) {
			cnt[i] += cnt[j];
		}
	}
	cout << cnt.back() << "\n";

	return 0;
}
