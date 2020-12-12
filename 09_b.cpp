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

constexpr long long need = 70639851;

int main() {
	vector<long long> a;
	long long x;
	while (cin >> x) {
		a.push_back(x);
	}
	for (int i = 0; i < (int)a.size(); ++i) {
		long long sum = 0;
		long long mn = LLONG_MAX;
		long long mx = LLONG_MIN;
		for (int j = i; j >= 0; --j) {
			mn = min(mn, a[j]);
			mx = max(mx, a[j]);
			sum += a[j];
			if (sum > need) {
				break;
			}
			if (sum == need) {
				if (i != j) {
					cout << mn + mx << "\n";
				}
				break;
			}
		}
	}

	return 0;
}
