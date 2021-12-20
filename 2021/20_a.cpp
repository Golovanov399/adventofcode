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

const int K = 2;
const int off = K + 5;
const int n = 100;
const int N = n + 2 * off;

int a[N][N];
int b[N][N];

int main() {
	string s;
	cin >> s;
	for (int i = 0; i < n; ++i) {
		string t;
		cin >> t;
		for (int j = 0; j < n; ++j) {
			a[i + off][j + off] = (t[j] == '#');
		}
	}

	for (int it = 0; it < 2; ++it) {
		memset(b, 0, sizeof(b));
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				int pos = 0;
				for (int x = -1; x <= 1; ++x) {
					for (int y = -1; y <= 1; ++y) {
						if (clamp(i + x, 0, N - 1) == i + x && clamp(j + y, 0, N - 1) == j + y) {
							pos = pos * 2 + a[i + x][j + y];
						} else {
							pos = pos * 2 + (it % 2);
						}
					}
				}
				b[i][j] = s[pos] == '#';
			}
		}
		memcpy(a, b, sizeof(b));
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				cerr << ".#"[a[i][j]];
			}
			cerr << "\n";
		}
		cerr << "\n";
	}

	int ans = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			ans += a[i][j];
		}
	}
	cout << ans << "\n";

	return 0;
}
