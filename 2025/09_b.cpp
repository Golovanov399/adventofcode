#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()

using namespace std;

inline int nxt() {
	int x;
	cin >> x;
	return x;
}

vector<int> read_ints() {
	vector<int> res;
	int x;
	while (cin >> x) {
		res.push_back(x);
	}
	return res;
}

vector<int> read_ints(const string& s) {
	stringstream sstr(s);
	vector<int> res;
	int x;
	while (sstr >> x) {
		res.push_back(x);
	}
	return res;
}

string read_line() {
	string s;
	getline(cin, s);
	return s;
}

vector<string> read_lines() {
	vector<string> res;
	string s;
	while (getline(cin, s)) {
		res.push_back(s);
	}
	return res;
}

struct Point {
	int x, y;
};

int main() {
	vector<Point> pts;
	string s;
	while (cin >> s) {
		int i = s.find(',');
		int x = stoi(s.substr(0, i));
		int y = stoi(s.substr(i + 1));
		pts.push_back({x, y});
	}
	const int n = pts.size();
	vector<int> all_xs, all_ys;
	{
		long long area = 0;
		for (int i = 0; i < n; ++i) {
			auto p = pts[i];
			auto q = pts[(i + 1) % n];
			all_xs.push_back(p.x);
			all_ys.push_back(p.y);
			assert(p.x == q.x || p.y == q.y);
			if (p.y == q.y) {
				area += 1ll * p.y * (p.x - q.x);
			}
		}
		if (area < 0) {
			reverse(all(pts));
		}
	}
	sort(all(all_xs));
	all_xs.resize(unique(all(all_xs)) - all_xs.begin());
	sort(all(all_ys));
	all_ys.resize(unique(all(all_ys)) - all_ys.begin());
	const int xn = all_xs.size();
	const int yn = all_ys.size();

	vector<vector<int>> p(xn + 1, vector<int>(yn + 1, 0));
	for (auto& pt : pts) {
		pt.x = lower_bound(all(all_xs), pt.x) - all_xs.begin();
		pt.y = lower_bound(all(all_ys), pt.y) - all_ys.begin();
	}
	for (int i = 0; i < n; ++i) {
		auto pt = pts[i];
		auto q = pts[(i + 1) % n];
		if (pt.y == q.y) {
			p[pt.x][pt.y] += 1;
			p[q.x][pt.y] -= 1;
		}
	}
	for (int i = xn; i >= 0; --i) {
		for (int j = yn; j >= 0; --j) {
			if (i + 1 <= xn) {
				p[i][j] += p[i + 1][j];
			}
			if (j + 1 <= yn) {
				p[i][j] += p[i][j + 1];
			}
			if (i + 1 <= xn && j + 1 <= yn) {
				p[i][j] -= p[i + 1][j + 1];
			}
		}
	}
	for (int i = 0; i <= xn; ++i) {
		for (int j = 0; j <= yn; ++j) {
			if (i) {
				p[i][j] += p[i - 1][j];
			}
			if (j) {
				p[i][j] += p[i][j - 1];
			}
			if (i && j) {
				p[i][j] -= p[i - 1][j - 1];
			}
		}
	}
	long long ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			int mx = min(pts[i].x, pts[j].x);
			int Mx = max(pts[i].x, pts[j].x);
			int my = min(pts[i].y, pts[j].y);
			int My = max(pts[i].y, pts[j].y);
			if (p[Mx][My] - p[mx][My] - p[Mx][my] + p[mx][my] == (Mx - mx) * (My - my)) { // wrong but let's try
				ans = max(ans, 1ll * (all_xs[Mx] - all_xs[mx] + 1) * (all_ys[My] - all_ys[my] + 1));
			}
		}
	}
	cout << ans << "\n";

	return 0;
}
