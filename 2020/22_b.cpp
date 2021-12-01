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
	vector<int> q[2];
	string s;
	int idx = -1;
	while (idx < 2 && cin >> s) {
		if (s == "Player") {
			++idx;
			cin >> s;
		} else {
			q[idx].push_back(stoi(s));
		}
	}


	auto calc = [&](auto self, vector<int>& a, vector<int>& b) -> int {
		set<pair<vector<int>, vector<int>>> S;
		// for (int x : a) {
		// 	cerr << x << " ";
		// }
		// cerr << "|";
		// for (int y : b) {
		// 	cerr << " " << y;
		// }
		// cerr << "\n";
		while (!a.empty() && !b.empty()) {
			if (S.count({a, b})) {
				return 0;
			}
			S.insert({a, b});
			int x = a[0];
			a.erase(a.begin());
			int y = b[0];
			b.erase(b.begin());
			int winner = -1;
			if ((int)a.size() >= x && (int)b.size() >= y) {
				auto aa = vector<int>(a.begin(), a.begin() + x);
				auto bb = vector<int>(b.begin(), b.begin() + y);
				winner = self(self, aa, bb);
			} else {
				winner = x < y;
			}
			if (winner == 0) {
				a.push_back(x);
				a.push_back(y);
			} else {
				b.push_back(y);
				b.push_back(x);
			}
		}
		return a.empty() ? 1 : 0;
	};

	idx = calc(calc, q[0], q[1]);

	int ans = 0;
	int n = q[idx].size();
	for (int x : q[idx]) {
		ans += n-- * x;
	}
	cout << ans << "\n";

	return 0;
}
