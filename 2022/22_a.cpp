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
	{
		int m = 0;
		for (auto s : a) {
			m = max(m, (int)s.size());
		}
		for (auto& s : a) {
			s += string(m - (int)s.size(), ' ');
		}
	}
	string movement;
	cin >> movement;

	int x = 0, y = 0;
	while (isspace(a[x][y])) {
		++y;
	}
	int dx = 0, dy = 1;
	int i = 0;

	auto step = [&](int x, int y, int dx, int dy) {
		while (true) {
			x += dx, y += dy;
			if (x < 0) {
				x = (int)a.size() - 1;
			}
			if (x >= (int)a.size()) {
				x = 0;
			}
			if (y < 0) {
				y = (int)a[x].size() - 1;
			}
			if (y >= (int)a[x].size()) {
				y = 0;
			}
			// cerr << x << " " << y << ", ";
			if (a[x][y] != ' ') {
				break;
			}
		}
		return pair{x, y};
	};

	while (i < (int)movement.size()) {
		int len = 0;
		while (i < (int)movement.size() && isdigit(movement[i])) {
			len = len * 10 + (movement[i] - '0');
			++i;
		}
		char c = (i == (int)movement.size()) ? 0 : movement[i++];

		for (int j = 0; j < len; ++j) {
			if (dy == 1) {
				a[x][y] = '>';
			}
			if (dx == 1) {
				a[x][y] = 'v';
			}
			if (dy == -1) {
				a[x][y] = '<';
			}
			if (dx == -1) {
				a[x][y] = '^';
			}
			auto [nx, ny] = step(x, y, dx, dy);
			if (a[nx][ny] == '#') {
				break;
			} else {
				x = nx, y = ny;
			}
		}
		if (c) {
			swap(dx, dy);
		}
		if (c == 'R') {
			dy *= -1;
		} else if (c == 'L') {
			dx *= -1;
		}
	}
	cout << 1000 * (x + 1) + 4 * (y + 1) + 2 * (dy == -1) + (dx == -1) << "\n";
	// for (auto s : a) {
	// 	cerr << s << "\n";
	// }
	// cerr << x << " " << y << " " << dx << " " << dy << "\n";

	return 0;
}
