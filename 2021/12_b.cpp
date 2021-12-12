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

bool islower(string s) {
	for (char c : s) {
		if (!islower(c)) {
			return false;
		}
	}
	return true;
}

int main() {
	map<string, vector<string>> M;
	string s;
	while (cin >> s) {
		string from, to;
		for (char c : s) {
			if (c == '-') {
				from = to;
				to = "";
			} else {
				to += c;
			}
		}
		M[from].push_back(to);
		M[to].push_back(from);
	}

	multiset<string> used;
	bool can = true;
	int ans = 0;
	function<void(string)> rec = [&](string s) {
		if (s == "end") {
			++ans;
			return;
		}
		if (islower(s)) {
			used.insert(s);
		}
		for (auto t : M.at(s)) {
			if (!used.contains(t)) {
				rec(t);
			} else if (can && t != "start") {
				can = false;
				rec(t);
				can = true;
			}
		}
		if (islower(s)) {
			used.erase(used.find(s));
		}
	};
	rec("start");
	cout << ans << "\n";

	return 0;
}
