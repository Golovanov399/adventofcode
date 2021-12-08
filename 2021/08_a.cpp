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
	int ans = 0;
	for (int i = 0; i < 200; ++i) {
		string s;
		for (int j = 0; j <= 10; ++j) {
			cin >> s;
		}
		for (int j = 0; j < 4; ++j) {
			cin >> s;
			if (s.length() == 2 || s.length() == 3 || s.length() == 4 || s.length() == 7) {
				++ans;
			}
		}
	}
	cout << ans << "\n";

	return 0;
}
