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
	int x, y, z;
};

ostream& operator <<(ostream& ostr, const Point& p) {
	return ostr << p.x << "," << p.y << "," << p.z;
}

long long sqr(long long x) {
	return x * x;
}

long long d(const Point& p, const Point& q) {
	return sqr(p.x - q.x) + sqr(p.y - q.y) + sqr(p.z - q.z);
}

int main() {
	vector<Point> pts;
	string s;
	while (cin >> s) {
		int i = s.find(',');
		int x = stoi(s.substr(0, i));
		s = s.substr(i + 1);
		i = s.find(',');
		int y = stoi(s.substr(0, i));
		int z = stoi(s.substr(i + 1));
		pts.push_back({x, y, z});
	}
	const int n = pts.size();
	vector<pair<int, int>> pairs;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			pairs.push_back({i, j});
		}
	}
	sort(all(pairs), [&](const auto& p, const auto& q) {
		return d(pts[p.first], pts[p.second]) < d(pts[q.first], pts[q.second]);
	});

	vector<int> color(n);
	iota(all(color), 0);
	vector<vector<int>> by_color(n);
	for (int i = 0; i < n; ++i) {
		by_color[i] = {i};
	}

	auto merge = [&](int u, int v) {
		u = color[u];
		v = color[v];
		if (u == v) {
			return false;
		}
		if (by_color[u].size() < by_color[v].size()) {
			swap(u, v);
		}
		for (int x : by_color[v]) {
			color[x] = u;
		}
		by_color[u].insert(by_color[u].end(), all(by_color[v]));
		by_color[v] = {};
		return true;
	};

	int rem = n - 1;
	long long prod = 0;
	for (auto [i, j] : pairs) {
		prod = pts[i].x * 1ll * pts[j].x;
		if (merge(i, j)) {
			--rem;
			if (rem == 0) {
				break;
			}
		}
	}
	cout << prod << "\n";

	return 0;
}
