#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define itn int
#define make_unique(x) sort((x).begin(), (x).end()); (x).erase(unique((x).begin(), (x).end()), (x).end())

using namespace std;

inline int nxt() {
	int x;
	cin >> x;
	return x;
}

int main() {
	vector<string> a;
	{
		string s;
		while (cin >> s) {
			a.push_back(s);
		}
	}

	const int n = a.size();
	const int m = a[0].size();
	vector<vector<char>> ok(n, vector<char>(m, 0));
	for (int i = 0; i < n; ++i) {
		int cur = -1;
		for (int j = 0; j < m; ++j) {
			int x = a[i][j] - '0';
			if (x > cur) {
				ok[i][j] = true;
				cur = x;
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		int cur = -1;
		for (int j = m - 1; j >= 0; --j) {
			int x = a[i][j] - '0';
			if (x > cur) {
				ok[i][j] = true;
				cur = x;
			}
		}
	}
	for (int j = 0; j < m; ++j) {
		int cur = -1;
		for (int i = 0; i < n; ++i) {
			int x = a[i][j] - '0';
			if (x > cur) {
				ok[i][j] = true;
				cur = x;
			}
		}
	}
	for (int j = 0; j < m; ++j) {
		int cur = -1;
		for (int i = n - 1; i >= 0; --i) {
			int x = a[i][j] - '0';
			if (x > cur) {
				ok[i][j] = true;
				cur = x;
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			ans += ok[i][j];
		}
	}
	cout << ans << "\n";

	return 0;
}
