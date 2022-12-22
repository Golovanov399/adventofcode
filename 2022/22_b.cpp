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

struct Point {
	int x, y, z;

	Point& operator +=(const Point& p) {
		x += p.x;
		y += p.y;
		z += p.z;
		return *this;
	}

	Point& operator -=(const Point& p) {
		x -= p.x;
		y -= p.y;
		z -= p.z;
		return *this;
	}

	Point operator -() const {
		return {-x, -y, -z};
	}

	bool operator <(const Point& p) const {
		return tie(x, y, z) < tie(p.x, p.y, p.z);
	}

	friend ostream& operator <<(ostream& ostr, const Point& p) {
		return ostr << "(" << p.x << ", " << p.y << ", " << p.z << ")";
	}
};

Point vp(const Point& p, const Point& q) {
	return {p.y * q.z - p.z * q.y, p.z * q.x - p.x * q.z, p.x * q.y - p.y * q.x};
}

int main() {
	vector<string> a;
	{
		string s;
		while (getline(cin, s)) {
			if (s == "") {
				break;
			}
			a.push_back(s);
		}
	}
	int n = a.size();
	int m = 0;
	{
		for (auto s : a) {
			m = max(m, (int)s.size());
		}
		for (auto& s : a) {
			s += string(m - (int)s.size(), ' ');
		}
	}
	string movement;
	cin >> movement;

	int sz = 0;
	for (auto s : a) {
		sz += count_if(all(s), [](char c) { return !isspace(c); });
	}
	sz = round(sqrt(sz / 6));
	cerr << sz << "\n";

	vector<vector<tuple<Point, Point, Point>>> where(n, vector<tuple<Point, Point, Point>>(m));
	{
		vector<vector<char>> used(n, vector<char>(m, false));
		vector<pair<int, int>> st;
		for (int j = 0; j < m; ++j) {
			if (!isspace(a[0][j])) {
				where[0][j] = {{0, 0, 0}, {1, 0, 0}, {0, 0, 1}};
				used[0][j] = true;
				st.push_back({0, j});
				break;
			}
		}
		while (!st.empty()) {
			auto [i, j] = st.back();
			st.pop_back();
			// cerr << i << " " << j << ": " << get<0>(where[i][j]) << " " << vp(get<1>(where[i][j]), get<2>(where[i][j])) << "\n";
			for (int di = -1; di <= 1; ++di) {
				for (int dj = -1; dj <= 1; ++dj) {
					if (abs(di) + abs(dj) != 1) {
						continue;
					}
					int ni = i + di, nj = j + dj;
					if (clamp(ni, 0, n - 1) != ni || clamp(nj, 0, m - 1) != nj || a[ni][nj] == ' ') {
						continue;
					}
					if (used[ni][nj]) {
						continue;
					}
					st.push_back({ni, nj});
					used[ni][nj] = true;
					if (i / sz == ni / sz && j / sz == nj / sz) {
						auto [pos, dx, dy] = where[i][j];
						if (di == 1) {
							pos += dx;
						}
						if (di == -1) {
							pos -= dx;
						}
						if (dj == 1) {
							pos += dy;
						}
						if (dj == -1) {
							pos -= dy;
						}
						where[ni][nj] = {pos, dx, dy};
					} else if (i / sz != ni / sz) {
						auto [pos, dx, dy] = where[i][j];
						auto dz = vp(dx, dy);
						if (di == 1) {
							dx = -dz;
						} else {
							dx = dz;
						}
						where[ni][nj] = {pos, dx, dy};
					} else if (j / sz != nj / sz) {
						auto [pos, dx, dy] = where[i][j];
						auto dz = vp(dx, dy);
						if (dj == 1) {
							dy = -dz;
						} else {
							dy = dz;
						}
						where[ni][nj] = {pos, dx, dy};
					} else {
						assert(false);
					}
				}
			}
		}
	}
	map<tuple<Point, Point, Point>, tuple<int, int, int, int>> M;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (!isspace(a[i][j])) {
				auto [pos, dx, dy] = where[i][j];
				auto dz = vp(dx, dy);
				// cerr << i << " " << j << ": " << pos << " " << dx << " " << dy << " " << dz << "\n";
				int di = 0, dj = 1;
				for (int it = 0; it < 4; ++it) {
					M[{pos, dz, dy}] = {i, j, di, dj};
					swap(di, dj);
					di *= -1;
					swap(dx, dy);
					dy = -dy;
				}
			}
		}
	}

	int i = 0, j = 0;
	while (isspace(a[i][j])) {
		++j;
	}
	int di = 0, dj = 1;
	auto [pos, dx, dy] = where[i][j];
	auto dz = vp(dx, dy);
	int ptr = 0;

	auto rot_l = [&]() {
		swap(di, dj);
		di *= -1;
		swap(dx, dy);
		dy = -dy;
	};
	auto rot_r = [&]() {
		swap(di, dj);
		dj *= -1;
		swap(dx, dy);
		dx = -dx;
	};
	auto step = [&]() {
		int ni = i + di, nj = j + dj;
		if (clamp(ni, 0, n - 1) == ni && clamp(nj, 0, m - 1) == nj && ni / sz == i / sz && nj / sz == j / sz) {
			i = ni;
			j = nj;
			pos += dy;
		} else {
			swap(dy, dz);
			dy = -dy;
			// cerr << pos << " " << dx << " " << dy << " " << dz << " ?\n";
			tie(i, j, di, dj) = M.at({pos, dz, dy});
		}
	};

	while (ptr < (int)movement.size()) {
		int len = 0;
		while (ptr < (int)movement.size() && isdigit(movement[ptr])) {
			len = len * 10 + (movement[ptr] - '0');
			++ptr;
		}
		char c = (ptr == (int)movement.size()) ? 0 : movement[ptr++];

		for (int it = 0; it < len; ++it) {
			if (dj == 1) {
				a[i][j] = '>';
			}
			if (di == 1) {
				a[i][j] = 'v';
			}
			if (dj == -1) {
				a[i][j] = '<';
			}
			if (di == -1) {
				a[i][j] = '^';
			}
			// cerr << pos << "\n";

			step();
			if (a[i][j] == '#') {
				rot_r();
				rot_r();
				step();
				rot_r();
				rot_r();
				break;
			}
		}
		if (c == 'R') {
			rot_r();
		} else if (c == 'L') {
			rot_l();
		}
	}
	cout << 1000 * (i + 1) + 4 * (j + 1) + 2 * (dj == -1) + (di != 0) + 2 * (di == -1) << "\n";
	// for (auto s : a) {
	// 	cerr << s << "\n";
	// }
	// cerr << i << " " << j << " " << di << " " << dj << "\n";

	return 0;
}
