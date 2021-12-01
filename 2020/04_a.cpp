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

const set<string> keys = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
const set<string> maybe = {"cid"};

int main() {
	int ans = 0;
	string s;
	set<string> cur;
	bool fail = false;
	while (getline(cin, s)) {
		if (s == "") {
			ans += !fail && cur.size() == keys.size();
			fail = false;
			cur.clear();
		}
		istringstream sstr(s);
		string t;
		while (sstr >> t) {
			if (t.find(':') == string::npos) {
				fail = true;
				break;
			}
			auto st = t.substr(0, t.find(':'));
			if (cur.count(st)) {
				fail = true;
			} else if (keys.count(st)) {
				cur.insert(st);
			} else if (!maybe.count(st)) {
				fail = true;
			}
		}
	}
	cout << ans << "\n";

	return 0;
}
