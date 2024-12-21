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

const map<char, pair<int, int>> numpads = []() {
	map<char, pair<int, int>> M;
	M['A'] = {1, 1};
	M['^'] = {1, 0};
	M['v'] = {0, 0};
	M['>'] = {0, 1};
	M['<'] = {0, -1};
	M['0'] = {1, 0};
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			M['1' + 3 * i + j] = {i + 2, j - 1};
		}
	}
	return M;
}();

map<pair<string, int>, long long> cache;

long long f(const string& s, int k) {
	if (k == 0) {
		return s.length();
	}

	if (auto it = cache.find({s, k}); it != cache.end()) {
		return it->second;
	}

	auto [x, y] = numpads.at('A');
	long long ans = 0;
	for (char c : s) {
		vector<pair<char, int>> need;
		auto [nx, ny] = numpads.at(c);
		if (ny < y) {
			need.push_back({'<', y - ny});
		}
		if (ny > y) {
			need.push_back({'>', ny - y});
		}
		if (nx < x) {
			need.push_back({'v', x - nx});
		}
		if (nx > x) {
			need.push_back({'^', nx - x});
		}
		long long res = 3e18;
		sort(all(need));
		do {
			int xx = x, yy = y;
			char ok = true;
			string tmp;
			for (auto [c, cc] : need) {
				tmp += string(cc, c);
				if (c == '<') {
					yy -= cc;
				} else if (c == '>') {
					yy += cc;
				} else if (c == '^') {
					xx += cc;
				} else if (c == 'v') {
					xx -= cc;
				} else {
					assert(false);
				}
				if (xx == 1 && yy == -1) {
					ok = false;
				}
			}
			if (!ok) {
				continue;
			}
			res = min(res, f(tmp + 'A', k - 1));
		} while (next_permutation(all(need)));
		x = nx;
		y = ny;
		ans += res;
	}
	return cache[{s, k}] = ans;
}

int main() {
	string s;
	long long ans = 0;
	while (cin >> s) {
		auto t = f(s, 26);
		string num;
		for (char c : s) {
			if (isdigit(c)) {
				num += c;
			}
		}
		ans += stoi(num) * t;
		// cout << s << ": " << f(f(f(s))) << "\n";
		// cout << f(s, 3) << "\n";
		// cout << f(s, 2) << "\n";
		// cout << f(s, 1) << "\n";
		// cout << f(s, 0) << "\n";
		// return 0;
	}
	cout << ans << "\n";

	return 0;
}
