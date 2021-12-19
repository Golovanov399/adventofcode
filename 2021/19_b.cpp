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

struct Point {
	int x, y, z;

	Point operator -(const Point& p) const {
		return {x - p.x, y - p.y, z - p.z};
	}

	Point operator +(const Point& p) const {
		return {x + p.x, y + p.y, z + p.z};
	}

	void permute(const vector<int>& p) {
		int q[3] = {x, y, z}, w[3];
		for (int i : {0, 1, 2}) {
			w[p[i]] = q[i];
		}
		x = w[0], y = w[1], z = w[2];
	}

	void permute_back(const vector<int>& p) {
		int q[3] = {x, y, z}, w[3];
		for (int i : {0, 1, 2}) {
			w[i] = q[p[i]];
		}
		x = w[0], y = w[1], z = w[2];
	}

	void sign(int mask) {
		if (mask & 1) {
			x = -x;
		}
		if (mask & 2) {
			y = -y;
		}
		if (mask & 4) {
			z = -z;
		}
	}

	bool operator <(const Point& p) const {
		return tie(x, y, z) < tie(p.x, p.y, p.z);
	}
};

const int inf = 1e9;
int dp[101][101];

int calc(vector<int> a, vector<int> b) {
	// for (auto x : a) {
	// 	cerr << x << " ";
	// }
	// cerr << "| ";
	// for (auto x : b) {
	// 	cerr << x << " ";
	// }
	// cerr << "\n";
	const int n = a.size(), m = b.size();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			dp[i][j] = 1;
			int l = i - 1, r = j - 1;
			while (l >= 0 && r >= 0) {
				if (a[i] - a[l] < b[j] - b[r]) {
					--l;
				} else if (a[i] - a[l] > b[j] - b[r]) {
					--r;
				} else {
					break;
				}
			}
			if (l >= 0 && r >= 0) {
				int dl = l, dr = r;
				while (dl >= 0 && a[dl] == a[l]) {
					--dl;
				}
				while (dr >= 0 && b[dr] == b[r]) {
					--dr;
				}
				for (int cl = l; cl > dl; --cl) {
					for (int cr = r; cr > dr; --cr) {
						dp[i][j] = max(dp[i][j], 1 + dp[cl][cr]);
					}
				}
			}
		}
	}
	int d = inf;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (dp[i][j] >= 12) {
				assert(d == inf || d == a[i] - b[j]);
				d = a[i] - b[j];
			}
		}
	}
	return d;
}

int main() {
	vector<vector<Point>> a;
	{
		string s;
		while (cin >> s) {
			if (s == "---") {
				a.push_back({});
				cin >> s;
				cin >> s;
				cin >> s;
			} else {
				int x = stoi(s.substr(0, s.find(',')));
				s = s.substr(s.find(',') + 1);
				int y = stoi(s.substr(0, s.find(',')));
				s = s.substr(s.find(',') + 1);
				int z = stoi(s);
				a.back().push_back({x, y, z});
			}
		}
	}

	const int n = a.size();
	vector<Point> sc(n, {inf, inf, inf});
	sc[0] = {0, 0, 0};

	while (any_of(all(sc), [](Point p) { return p.x == inf; })) {
		for (int i0 = 0; i0 < n; ++i0) {
			if (sc[i0].x == inf) {
				continue;
			}
			vector<int> x0, y0, z0;
			for (auto p : a[i0]) {
				x0.push_back(p.x);
				y0.push_back(p.y);
				z0.push_back(p.z);
			}
			sort(all(x0));
			sort(all(y0));
			sort(all(z0));
			for (int i = 0; i < n; ++i) {
				if (sc[i].x < inf) {
					continue;
				}
				vector<int> perm(3);
				iota(all(perm), 0);
				vector<Point> corr;
				int cx = inf, cy = inf, cz = inf;
				do {
					for (auto& p : a[i]) {
						p.permute(perm);
					}
					for (int mask = 0; mask < 8; ++mask) {
						for (auto& p : a[i]) {
							p.sign(mask);
						}
						vector<int> xi, yi, zi;
						for (auto p : a[i]) {
							xi.push_back(p.x);
							yi.push_back(p.y);
							zi.push_back(p.z);
						}
						sort(all(xi));
						sort(all(yi));
						sort(all(zi));
						int x = calc(x0, xi);
						int y = calc(y0, yi);
						int z = calc(z0, zi);
						if (max({x, y, z}) < inf) {
							assert(cx == inf);
							cx = x;
							cy = y;
							cz = z;
							corr = a[i];
						}
						for (auto& p : a[i]) {
							p.sign(mask);
						}
					}
					for (auto& p : a[i]) {
						p.permute_back(perm);
					}
				} while (next_permutation(all(perm)));
				if (cx < inf) {
					cerr << "found " << i << " relative to " << i0 << "\n";
					sc[i] = {cx, cy, cz};
					sc[i] = sc[i0] + sc[i];
					cerr << "at " << sc[i].x << "," << sc[i].y << "," << sc[i].z << "\n";
					a[i] = corr;
				}
			}
		}
	}

	int ans = 0;
	for (auto p : sc) {
		for (auto q : sc) {
			ans = max(ans, abs(p.x - q.x) + abs(p.y - q.y) + abs(p.z - q.z));
		}
	}
	cout << ans << "\n";

	// set<Point> pts;
	// for (int i = 0; i < n; ++i) {
	// 	for (auto p : a[i]) {
	// 		pts.insert(p + sc[i]);
	// 	}
	// }
	// cout << pts.size() << "\n";

	return 0;
}
