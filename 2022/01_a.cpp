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

int main() {
	int mx = 0;
	int cur = 0;
	string s;
	while (getline(cin, s)) {
		if (s == "") {
			mx = max(mx, cur);
			cur = 0;
			continue;
		}
		cur += stoi(s);
	}
	cout << mx << "\n";

	return 0;
}
