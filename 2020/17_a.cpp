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

const int N = 30;
const int off = N / 2;

char dp[N][N][N];
char tmp[N][N][N];

int neigs(int x, int y, int z) {
	int res = 0;
	for (int dx = -1; dx <= 1; ++dx) {
		for (int dy = -1; dy <= 1; ++dy) {
			for (int dz = -1; dz <= 1; ++dz) {
				int nx = x + dx;
				int ny = y + dy;
				int nz = z + dz;
				if (nx >= 0 && nx < N - 1 && ny >= 0 && ny < N - 1 && nz >= 0 && nz < N - 1 && (dx || dy || dz)) {
					res += dp[nx][ny][nz];
				}
			}
		}
	}
	return res;
}

void cycle() {
	memset(tmp, 0, sizeof(tmp));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < N; ++k) {
				int nei = neigs(i, j, k);
				if (dp[i][j][k]) {
					tmp[i][j][k] = (nei >= 2 && nei <= 3);
				} else {
					tmp[i][j][k] = (nei == 3);
				}
			}
		}
	}
	memcpy(dp, tmp, sizeof(dp));
}

int main() {
	string s;
	int cur = off;
	while (cin >> s) {
		for (int i = 0; i < (int)s.size(); ++i) {
			dp[cur][off + i][off] = (s[i] == '#');
		}
		cur += 1;
	}

	for (int i = 0; i < 6; ++i) {
		cycle();
	}

	int ans = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < N; ++k) {
				ans += dp[i][j][k];
			}
		}
	}
	cout << ans << "\n";
	return 0;
}
