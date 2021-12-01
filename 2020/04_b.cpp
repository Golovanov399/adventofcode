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

int to_int(string s) {
	if (s.empty() || s[0] == '0') {
		return -1;
	}
	for (char c : s) {
		if (!isdigit(c)) {
			return -1;
		}
	}
	return stoi(s);
}

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
				auto val = t.substr(t.find(':') + 1);
				if (st == "byr") {
					if (val.size() != 4) {
						fail = true;
					} else {
						int x = to_int(val);
						if (!fail && clamp(x, 1920, 2002) != x) {
							fail = true;
						}
					}
				} else if (st == "iyr") {
					if (val.size() != 4) {
						fail = true;
					} else {
						int x = to_int(val);
						if (!fail && clamp(x, 2010, 2020) != x) {
							fail = true;
						}
					}
				} else if (st == "eyr") {
					if (val.size() != 4) {
						fail = true;
					} else {
						int x = to_int(val);
						if (!fail && clamp(x, 2020, 2030) != x) {
							fail = true;
						}
					}
				} else if (st == "hgt") {
					if (val.size() <= 2ul || (val.substr(val.size() - 2) != "cm" && val.substr(val.size() - 2) != "in")) {
						fail = true;
					} else {
						int x = to_int(val.substr(0, val.size() - 2ul));
						if (val.substr(val.size() - 2) == "cm") {
							fail |= clamp(x, 150, 193) != x;
						} else {
							fail |= clamp(x, 59, 76) != x;
						}
					}
				} else if (st == "hcl") {
					if (val.size() != 7ul || val[0] != '#') {
						fail = true;
					} else {
						for (char c : val.substr(1)) {
							if (!isdigit(c) && (c < 'a' && c > 'h')) {
								fail = true;
							}
						}
					}
				} else if (st == "ecl") {
					if (val != "amb" && val != "blu" && val != "brn" && val != "gry" && val != "grn" && val != "hzl" && val != "oth") {
						fail = true;
					}
				} else if (st == "pid") {
					if (val.size() != 9ul) {
						fail = true;
					} else {
						for (char c : val) {
							if (!isdigit(c)) {
								fail = true;
							}
						}
					}
				}
				cur.insert(st);
			} else if (!maybe.count(st)) {
				fail = true;
			}
		}
	}
	cout << ans << "\n";

	return 0;
}
