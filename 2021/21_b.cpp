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

const int N = 21;
const int K = 10;
pair<long long, long long> dp[N][N][K][K];

const int oc = 10;
long long pr[oc];

int main() {
	int p[2];
	{
		string st;
		cin >> st;
		cin >> st;
		cin >> st;
		cin >> st;
		cin >> p[0];
		cin >> st;
		cin >> st;
		cin >> st;
		cin >> st;
		cin >> p[1];
	}
	--p[0];
	--p[1];

	pr[0] = 1;
	for (int it = 0; it < 3; ++it) {
		for (int i = oc - 1; i >= 0; --i) {
			pr[i] = 0;
			for (int j = 1; j <= 3 && j <= i; ++j) {
				pr[i] += pr[i - j];
			}
		}
	}

	for (int s = 2 * N - 1; s >= 0; --s) {
		for (int i = 0; i <= s; ++i) {
			int j = s - i;
			if (i >= N || j >= N) {
				continue;
			}
			for (int p0 = 0; p0 < K; ++p0) {
				for (int p1 = 0; p1 < K; ++p1) {
					dp[i][j][p0][p1] = {0, 0};
					for (int d = 1; d < oc; ++d) {
						int np = (p0 + d) % K;
						if (i + np + 1 >= N) {
							dp[i][j][p0][p1].first += pr[d];
						} else {
							dp[i][j][p0][p1].first += dp[j][i + np + 1][p1][np].second * pr[d];
							dp[i][j][p0][p1].second += dp[j][i + np + 1][p1][np].first * pr[d];
						}
					}
				}
			}
		}
	}
	cout << max(dp[0][0][p[0]][p[1]].first, dp[0][0][p[0]][p[1]].second) << "\n";

	return 0;
}
