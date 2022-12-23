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

bool starts_with(string s, string t) {
	return s.length() >= t.length() && s.substr(0, t.length()) == t;
}

vector<string> split(string s, string by = " ") {
	vector<string> res = {""};
	for (int i = 0; i < (int)s.length(); ++i) {
		if (s.substr(i, by.length()) == by) {
			res.push_back("");
			i += (int)by.length() - 1;
		} else {
			res.back() += s[i];
		}
	}
	return res;
}

vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int main() {
	set<pair<int, int>> S;
	{
		string s;
		int i = 0;
		while (cin >> s) {
			for (int j = 0; j < (int)s.length(); ++j) {
				if (s[j] == '#') {
					S.insert({i, j});
				}
			}
			++i;
		}
	}

	for (int it = 0; it < 10; ++it) {
		map<pair<int, int>, vector<pair<int, int>>> prop;
		for (auto [x, y] : S) {
			bool ok = false;
			for (int dx = -1; dx <= 1; ++dx) {
				for (int dy = -1; dy <= 1; ++dy) {
					if ((dx || dy) && S.contains({x + dx, y + dy})) {
						ok = true;
					}
				}
			}
			if (!ok) {
				continue;
			}
			for (int i = 0; i < 4; ++i) {
				auto [dx, dy] = dirs[i];
				if (!S.contains({x + dx, y + dy}) && !S.contains({x + dx + dy, y + dy + dx}) && !S.contains({x + dx - dy, y + dy - dx})) {
					prop[{x + dx, y + dy}].push_back({x, y});
					break;
				}
			}
		}
		for (auto [where, whos] : prop) {
			if ((int)whos.size() == 1) {
				S.erase(whos[0]);
				S.insert(where);
			}
		}

		rotate(dirs.begin(), 1 + all(dirs));
	}

	int minx = 1e9, maxx = -1e9, miny = 1e9, maxy = -1e9;
	for (auto [x, y] : S) {
		minx = min(minx, x);
		maxx = max(maxx, x);
		miny = min(miny, y);
		maxy = max(maxy, y);
	}
	vector<string> a(maxx - minx + 1, string(maxy - miny + 1, '.'));
	for (auto [x, y] : S) {
		a[x - minx][y - miny] = '#';
	}
	// for (auto s : a) {
	// 	cerr << s << "\n";
	// }
	cout << (maxx - minx + 1) * (maxy - miny + 1) - (int)S.size() << "\n";

	return 0;
}
