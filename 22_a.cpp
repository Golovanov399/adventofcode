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
	queue<int> q[2];
	string s;
	int idx = -1;
	while (idx < 2 && cin >> s) {
		if (s == "Player") {
			++idx;
			cin >> s;
		} else {
			q[idx].push(stoi(s));
		}
	}

	while (!q[0].empty() && !q[1].empty()) {
		int x = q[0].front();
		q[0].pop();
		int y = q[1].front();
		q[1].pop();
		if (x > y) {
			q[0].push(x);
			q[0].push(y);
		} else {
			q[1].push(y);
			q[1].push(x);
		}
	}

	idx = 0;
	while (q[idx].empty()) {
		++idx;
	}
	int ans = 0;
	int n = q[idx].size();
	while (n) {
		ans += n * q[idx].front();
		--n;
		q[idx].pop();
	}
	cout << ans << "\n";

	return 0;
}
