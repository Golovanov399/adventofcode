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

	int ans = 0;
	int x = 0, y = 0;
	while (x < (int)a.size()) {
		if (a[x][y] == '#') {
			++ans;
		}
		y += 3;
		y %= a[x].size();
		x += 1;
	}
	cout << ans << "\n";

	return 0;
}
