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

const int n = 137, m = 139;
string a[n];

bool mv[max(n, m)];

bool step() {
	bool ok = false;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			mv[j] = a[i][j] == '>' && a[i][(j + 1) % m] == '.';
		}
		for (int j = 0; j < m; ++j) {
			if (mv[j]) {
				swap(a[i][j], a[i][(j + 1) % m]);
				ok = true;
			}
		}
	}
	for (int j = 0; j < m; ++j) {
		for (int i = 0; i < n; ++i) {
			mv[i] = a[i][j] == 'v' && a[(i + 1) % n][j] == '.';
		}
		for (int i = 0; i < n; ++i) {
			if (mv[i]) {
				swap(a[i][j], a[(i + 1) % n][j]);
				ok = true;
			}
		}
	}
	return ok;
}

int main() {
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}

	int ans = 0;
	while (true) {
		++ans;
		if (!step()) {
			break;
		} else {
			// for (int i = 0; i < n; ++i) {
			// 	cerr << a[i] << "\n";
			// }
			// cerr << "\n";
		}
	}
	cout << ans << "\n";

	return 0;
}
