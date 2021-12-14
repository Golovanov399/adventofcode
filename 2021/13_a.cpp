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
	vector<pair<int, int>> a;
	string s;
	while (cin >> s) {
		if (s[0] == 'f') {
			cin >> s;
			cin >> s;
			char c = s[0];
			int v = stoi(s.substr(2));
			for (auto& [x, y] : a) {
				if (c == 'x') {
					x = min(x, 2 * v - x);
				} else {
					y = min(y, 2 * v - y);
				}
			}
			make_unique(a);
			cout << a.size() << "\n";
		} else {
			int idx = s.find(',');
			int x = stoi(s.substr(0, idx)), y = stoi(s.substr(idx + 1));
			a.push_back({x, y});
		}
	}

	return 0;
}
