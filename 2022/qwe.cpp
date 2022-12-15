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

int sign(int x) {
	return x < 0 ? -1 : x > 0;
}

int main() {
	vector<tuple<int, int, int>> rhombs;
	[[maybe_unused]] vector<pair<int, int>> beacons;
	{
		string s;
		while (getline(cin, s)) {
			auto tokens = split(s, " ");
			int sx = stoi(tokens[2].substr(2, (int)tokens[2].size() - 3));
			int sy = stoi(tokens[3].substr(2, (int)tokens[3].size() - 3));
			int bx = stoi(tokens[8].substr(2, (int)tokens[8].size() - 3));
			int by = stoi(tokens[9].substr(2));
			beacons.emplace_back(bx, by);
			int d = abs(bx - sx) + abs(by - sy);
			rhombs.emplace_back(sx, sy, d);
		}
	}
	make_unique(beacons);

	int lb = 0, rb = 4e6 + 1;
	int skipped = -1;
	auto calc_y = [&](int yy) {
		vector<pair<int, int>> segs;
		for (auto [x, y, d] : rhombs) {
			if (abs(y - yy) > d) {
				continue;
			}
			int rest = d - abs(y - yy);
			segs.push_back({x - rest, x + rest + 1});
		}
		sort(all(segs));
		int last = lb;
		int ans = 0;
		for (auto [l, r] : segs) {
			if (r <= last) {
				continue;
			}
			r = min(r, rb);
			if (l > last) {
				skipped = last;
				ans += r - l;
			} else {
				ans += r - last;
			}
			last = r;
		}

		return ans;
	};

	for (int y = lb; y < rb; ++y) {
		if (calc_y(y) < rb - lb) {
			cerr << skipped << ", " << y << "\n";
			cout << skipped * 1ll * (rb - 1) + y << "\n";
			// break;
		}
	}

	return 0;
}
