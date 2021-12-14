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
	cin >> s;

	string from, arrow, to;
	map<string, char> M;
	while (cin >> from >> arrow >> to) {
		M[from] = to[0];
	}

	for (int it = 0; it < 10; ++it) {
		string t = string("") + s[0];
		for (int i = 1; i < (int)s.size(); ++i) {
			if (auto it = M.find(s.substr(i - 1, 2)); it != M.end()) {
				t += it->second;
			}
			t += s[i];
		}
		s.swap(t);
	}

	map<char, int> qnt;
	for (char c : s) {
		qnt[c] += 1;
	}
	vector<int> cnts;
	for (auto p : qnt) {
		cnts.push_back(p.second);
	}
	sort(all(cnts));
	cout << cnts.back() - cnts[0] << "\n";

	return 0;
}
