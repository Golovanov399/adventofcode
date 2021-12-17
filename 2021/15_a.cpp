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

const int n = 100;
int a[n][n];
int dp[n][n];

int main() {
	string s;
	for (int i = 0; i < n; ++i) {
		cin >> s;
		for (int j = 0; j < n; ++j) {
			a[i][j] = s[j] - '0';
		}
	}
	set<array<int, 3>> S;
	S.insert({{0, 0, 0}});
	memset(dp, -1, sizeof(dp));
	dp[0][0] = 0;
	while (!S.empty()) {
		auto [val, x, y] = *S.begin();
		S.erase(S.begin());
		for (int dx : {-1, 0, 1}) {
			for (int dy : {-1, 0, 1}) {
				if (abs(dx) + abs(dy) != 1) {
					continue;
				}
				int nx = x + dx, ny = y + dy;
				if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
					continue;
				}
				int nval = val + a[nx][ny];
				if (dp[nx][ny] > -1 && dp[nx][ny] <= nval) {
					continue;
				}
				S.erase({dp[nx][ny], nx, ny});
				dp[nx][ny] = nval;
				S.insert({dp[nx][ny], nx, ny});
			}
		}
	}

	cout << dp[n - 1][n - 1] << "\n";

	return 0;
}
