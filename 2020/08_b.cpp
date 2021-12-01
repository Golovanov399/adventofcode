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

	const int n = a.size();
	for (int j = 0; j < n; ++j) {
		if (a[j].first == "acc") {
			continue;
		}
		a[j].first = (a[j].first == "nop") ? "jmp" : "nop";
		int acc = 0;
		vector<char> used(n);
		int i = 0;
		while (i >= 0 && i < n && !used[i]) {
			used[i] = 1;
			if (a[i].first == "acc") {
				acc += a[i].second;
				i += 1;
			} else if (a[i].first == "nop") {
				i += 1;
			} else {
				assert(a[i].first == "jmp");
				i += a[i].second;
			}
		}
		if (i == n) {
			cout << acc << "\n";
		}
		a[j].first = (a[j].first == "nop") ? "jmp" : "nop";
	}

	return 0;
}
