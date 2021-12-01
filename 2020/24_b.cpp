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
	string s;
	set<pair<int, int>> S;
	while (cin >> s) {
		int x = 0, y = 0;
		int i = 0;
		while (i < (int)s.length()) {
			if (s[i] == 'e') {
				++x;
				i += 1;
			} else if (s[i] == 'w') {
				--x;
				i += 1;
			} else if (s[i] == 's') {
				++i;
				--y;
				if (s[i] == 'e') {
					++x;
				}
				i += 1;
			} else if (s[i] == 'n') {
				++i;
				++y;
				if (s[i] == 'w') {
					--x;
				}
				i += 1;
			}
		}
		pair p{x, y};
		if (S.count(p)) {
			S.erase(p);
		} else {
			S.insert(p);
		}
	}
	
	for (int i = 0; i < 100; ++i) {
		map<pair<int, int>, int> M;
		for (auto [x, y] : S) {
			M[{x - 1, y}] += 1;
			M[{x - 1, y + 1}] += 1;
			M[{x, y + 1}] += 1;
			M[{x + 1, y}] += 1;
			M[{x + 1, y - 1}] += 1;
			M[{x, y - 1}] += 1;
		}
		set<pair<int, int>> T;
		for (auto [p, c] : M) {
			if ((S.count(p) && (c == 1 || c == 2)) || (!S.count(p) && c == 2)) {
				T.insert(p);
			}
		}
		S.swap(T);
		if (i < 10) {
			cerr << i + 1 << ": " << S.size() << "\n";
		}
	}
	cout << S.size() << "\n";

	return 0;
}
