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

struct Point {
	int x, y;
};

Point parse(const string& s) {
	auto xy = split(s, ",");
	return {stoi(xy[0]), stoi(xy[1])};
}

int main() {
	string s;
	vector<pair<Point, Point>> segs;
	while (getline(cin, s)) {
		auto pts = split(s, " -> ");
		Point last = parse(pts[0]);
		segs.push_back({last, last});
		for (int i = 1; i < (int)pts.size(); ++i) {
			Point cur = parse(pts[i]);
			segs.push_back({last, cur});
			last = cur;
		}
	}

	int maxy = 0, maxx = 0;
	for (auto s : segs) {
		maxy = max(maxy, s.second.y);
		maxx = max(maxx, s.second.x);
	}

	vector<vector<char>> used(2 * maxy + maxx + 1, vector<char>(maxy + 3, 0));
	for (auto [fst, snd] : segs) {
		Point delta{sign(snd.x - fst.x), sign(snd.y - fst.y)};
		auto p = fst;
		used[maxy + p.x][p.y] = true;
		while (p.x != snd.x || p.y != snd.y) {
			p.x += delta.x;
			p.y += delta.y;
			used[maxy + p.x][p.y] = true;
		}
	}
	for (int i = 0; i < (int)used.size(); ++i) {
		used[i][maxy + 2] = true;
	}
	// cerr << "gray ";
	// for (int i = 0; i <= maxx; ++i) {
	// 	for (int j = 0; j <= maxy; ++j) {
	// 		if (used[i][j]) {
	// 			cerr << i << " " << -j << " ";
	// 		}
	// 	}
	// }
	// cerr << "\nred ";
	int ans = 0;
	while (true) {
		int x = 500, y = 0;
		if (used[maxy + x][y]) {
			break;
		}
		while (true) {
			bool stable = false;
			for (int opt : {0, -1, 1, 228}) {
				int nx = x + opt;
				int ny = y + 1;
				if (opt == 228) {
					stable = true;
					break;
				} else if (!used[maxy + nx][ny]) {
					x = nx, y = ny;
					break;
				}
			}
			if (stable) {
				// cerr << x << " " << -y << " ";
				used[maxy + x][y] = true;
				++ans;
				break;
			}
		}
	}
	cout << ans << "\n";

	return 0;
}
