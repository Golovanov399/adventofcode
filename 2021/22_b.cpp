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

struct Range {
	int from, to;
};

array<Range, 3> parse(string s) {
	s += ',';
	array<Range, 3> res;
	for (auto& r : res) {
		int pos = s.find(',');
		auto t = s.substr(0, pos);
		s = s.substr(pos + 1);
		t = t.substr(2);
		pos = t.find("..");
		r.from = stoi(t.substr(0, pos));
		r.to = stoi(t.substr(pos + 2));
	}
	return res;
}

struct Op {
	array<Range, 3> r;
	int val;
};

const int N = 840;
char st[N][N][N];

int main() {
	string type;
	string s;
	vector<Op> ops;
	vector<int> xs, ys, zs;
	while (cin >> type >> s) {
		auto r = parse(s);
		int val = type == "on";
		ops.push_back({r, val});
		xs.push_back(r[0].to);
		xs.push_back(r[0].from - 1);
		ys.push_back(r[1].to);
		ys.push_back(r[1].from - 1);
		zs.push_back(r[2].to);
		zs.push_back(r[2].from - 1);
	}
	make_unique(xs);
	make_unique(ys);
	make_unique(zs);
	for (auto [r, v] : ops) {
		int fi = lower_bound(all(xs), r[0].from - 1) - xs.begin();
		int fj = lower_bound(all(ys), r[1].from - 1) - ys.begin();
		int fk = lower_bound(all(zs), r[2].from - 1) - zs.begin();
		int ti = lower_bound(all(xs), r[0].to) - xs.begin();
		int tj = lower_bound(all(ys), r[1].to) - ys.begin();
		int tk = lower_bound(all(zs), r[2].to) - zs.begin();
		for (int i = fi; i < ti; ++i) {
			for (int j = fj; j < tj; ++j) {
				for (int k = fk; k < tk; ++k) {
					st[i][j][k] = v;
				}
			}
		}
	}

	long long ans = 0;
	for (int i = 0; i < (int)xs.size() - 1; ++i) {
		for (int j = 0; j < (int)ys.size() - 1; ++j) {
			for (int k = 0; k < (int)zs.size() - 1; ++k) {
				int x = xs[i + 1], y = ys[j + 1], z = zs[k + 1];
				// int state = 0;
				// for (auto [r, v] : ops) {
				// 	if (clamp(x, r[0].from, r[0].to) == x && clamp(y, r[1].from, r[1].to) == y && clamp(z, r[2].from, r[2].to) == z) {
				// 		state = v;
				// 	}
				// }
				if (st[i][j][k]) {
					ans += 1ll * (xs[i + 1] - xs[i]) * (ys[j + 1] - ys[j]) * (zs[k + 1] - zs[k]);
				}
			}
		}
	}
	cout << ans << "\n";

	return 0;
}
