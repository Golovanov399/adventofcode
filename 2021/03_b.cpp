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
	auto b = a;
	for (int i = 0; (int)a.size() > 1; ++i) {
		vector<string> by[2];
		for (auto s : a) {
			by[s[i] - '0'].push_back(s);
		}
		a = (by[0].size() > by[1].size()) ? by[0] : by[1];
	}
	for (int i = 0; (int)b.size() > 1; ++i) {
		vector<string> by[2];
		for (auto s : b) {
			by[s[i] - '0'].push_back(s);
		}
		b = (by[0].size() <= by[1].size()) ? by[0] : by[1];
	}
	int x = 0, y = 0;
	for (char c : a[0]) {
		x = x * 2 + c - '0';
	}
	for (char c : b[0]) {
		y = y * 2 + c - '0';
	}
	cout << x * y << "\n";

	return 0;
}
