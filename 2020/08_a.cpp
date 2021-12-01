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
	vector<pair<string, int>> a;
	string s;
	int x;
	while (cin >> s >> x) {
		a.push_back({s, x});
	}
	int acc = 0;
	const int n = a.size();
	vector<char> used(n);
	int i = 0;
	while (!used[i]) {
		used[i] = 1;
		if (a[i].first == "acc") {
			acc += a[i].second;
			i += 1;
		} else if (a[i].first == "nop") {
			i += 1;
		} else {
			assert(a[i].first == "jmp");
			i += a[i].second;
			i = clamp(i, 0, n - 1);
		}
	}
	cout << acc << "\n";

	return 0;
}
