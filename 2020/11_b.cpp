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
	vector<string> a;
	string s;
	while (cin >> s) {
		a.push_back(s);
	}
	auto calc = [&](int x, int y) {
		int cnt = 0;
		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				if (!i && !j) {
					continue;
				}
				int nx = x + i, ny = y + j;
				while (nx >= 0 && nx < (int)a.size() && ny >= 0 && ny < (int)a[x].size()) {
					if (a[nx][ny] == '#') {
						++cnt;
						break;
					} else if (a[nx][ny] == 'L') {
						break;
					}
					nx += i;
					ny += j;
				}
			}
		}
		return cnt;
	};
	while (true) {
		auto b = a;
		for (int i = 0; i < (int)a.size(); ++i) {
			for (int j = 0; j < (int)a[i].size(); ++j) {
				if (a[i][j] == 'L') {
					b[i][j] = (calc(i, j) == 0) ? '#' : 'L';
				} else if (a[i][j] == '#') {
					b[i][j] = (calc(i, j) >= 5) ? 'L' : '#';
				}
			}
		}
		if (a == b) {
			break;
		}
		a.swap(b);
	}
	int ans = 0;
	for (auto s : a) {
		ans += count(all(s), '#');
	}
	cout << ans << "\n";

	return 0;
}
