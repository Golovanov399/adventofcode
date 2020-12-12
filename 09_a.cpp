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

constexpr int N = 25;

int main() {
	vector<long long> a;
	long long x;
	while (cin >> x) {
		if ((int)a.size() < N) {
			a.push_back(x);
		} else {
			bool ok = false;
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < i; ++j) {
					if (a[i] + a[j] == x) {
						ok = true;
						break;
					}
				}
			}
			if (!ok) {
				cout << x << "\n";
				break;
			} else {
				a.push_back(x);
				a.erase(a.begin());
			}
		}
	}

	return 0;
}
