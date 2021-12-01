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
	for (int i = 0; i < (int)a.size(); ++i) {
		for (int j = 0; j < i; ++j) {
			for (int k = 0; k < j; ++k) {
				if (a[i] + a[j] + a[k] == 2020) {
					cout << a[i] * a[j] * a[k] << "\n";
				}
			}
		}
	}

	return 0;
}
