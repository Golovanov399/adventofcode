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

pair<int, int> f(string s) {
	int i = s.find('-');
	return {stoi(s.substr(0, i)), stoi(s.substr(i + 1))};
}

bool cont(pair<int, int> p, pair<int, int> q) {
	return p.first <= q.first && q.second <= p.second;
}

int main() {
	string s;
	int ans = 0;
	while (cin >> s) {
		int i = s.find(',');
		auto p1 = f(s.substr(0, i)), p2 = f(s.substr(i + 1));
		if (cont(p1, p2) || cont(p2, p1)) {
			++ans;
		}
	}
	cout << ans << "\n";

	return 0;
}
