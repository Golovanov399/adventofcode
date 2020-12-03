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

	long long answer = 1;
	for (auto [p, q] : vector<pair<int, int>>{{1, 1}, {1, 3}, {1, 5}, {1, 7}, {2, 1}}) {
		int ans = 0;
		int x = 0, y = 0;
		while (x < (int)a.size()) {
			if (a[x][y] == '#') {
				++ans;
			}
			y += q;
			y %= a[x].size();
			x += p;
		}
		answer *= ans;
	}
	cout << answer << "\n";

	return 0;
}
