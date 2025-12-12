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

using u32 = uint32_t;

struct Shape {
	int w, h;
	vector<vector<u32>> options;

	static Shape from_str(vector<string> a) {
		int w = a[0].size();
		int h = a.size();
		vector<vector<u32>> res;
		for ([[maybe_unused]] int it : {0, 1}) {
			for (int idx = 0; idx < 4; ++idx) {
				vector<u32> masks(a.size());
				vector<string> b(a[0].size(), string(a.size(), '.'));
				for (int i = 0; i < (int)a.size(); ++i) {
					for (int j = 0; j < (int)a[i].size(); ++j) {
						if (a[i][j] == '#') {
							masks[i] |= 1u << j;
							b[j][(int)a.size() - 1 - i] = '#';
						}
					}
				}
				res.push_back(masks);
				a.swap(b);
			}
			for (auto& s : a) {
				reverse(all(s));
			}
		}
		return {w, h, res};
	}
};

bool rec(int w, int h, const vector<Shape>& shapes, vector<u32>& masks, vector<int>& cnts, int rem, int i, int j) {
	if (rem == 0) {
		return true;
	}
	if (j == w) {
		j = 0;
		++i;
	}
	if (i == h) {
		return false;
	}
	for (int idx = 0; idx < (int)shapes.size(); ++idx) {
		if (!cnts[idx]) {
			continue;
		}
		if (i + shapes[idx].h <= h && j + shapes[idx].w <= w) {
			--cnts[idx];
			for (int oi = 0; oi < 8; oi += 2) {
				bool ok = true;
				for (int ri = 0; ri < (int)shapes[idx].options[oi].size(); ++ri) {
					ok &= !(masks[i + ri] & (shapes[idx].options[oi][ri] << j));
					masks[i + ri] ^= shapes[idx].options[oi][ri] << j;
				}
				if (ok && rec(w, h, shapes, masks, cnts, rem - 1, i, j + 1)) {
					return true;
				}
				for (int ri = 0; ri < (int)shapes[idx].options[oi].size(); ++ri) {
					masks[i + ri] ^= shapes[idx].options[oi][ri] << j;
				}
			}
			++cnts[idx];
		}
		if (i + shapes[idx].w <= h && j + shapes[idx].h <= w) {
			--cnts[idx];
			for (int oi = 1; oi < 8; oi += 2) {
				bool ok = true;
				for (int ri = 0; ri < (int)shapes[idx].options[oi].size(); ++ri) {
					ok &= !(masks[i + ri] & (shapes[idx].options[oi][ri] << j));
					masks[i + ri] ^= shapes[idx].options[oi][ri] << j;
				}
				if (ok && rec(w, h, shapes, masks, cnts, rem - 1, i, j + 1)) {
					return true;
				}
				for (int ri = 0; ri < (int)shapes[idx].options[oi].size(); ++ri) {
					masks[i + ri] ^= shapes[idx].options[oi][ri] << j;
				}
			}
			++cnts[idx];
		}
	}
	return rec(w, h, shapes, masks, cnts, rem, i, j + 1);
}

bool can(int w, int h, const vector<Shape>& shapes, vector<int> cnts) {
	const int total_cnt = accumulate(all(cnts), 0);
	if (total_cnt <= (w / 3) * (h / 3)) {
		// cerr << "3x3\n";
		return true;
	}
	{
		int area = w * h;
		for (int i = 0; i < (int)shapes.size(); ++i) {
			int a = 0;
			for (auto x : shapes[i].options[0]) {
				a += __builtin_popcount(x);
			}
			area -= a * cnts[i];
		}
		if (area < 0) {
			// cerr << "area\n";
			return false;
		}
	}
	assert(false);
	// cerr << "idk\n";
	// return false;
	// vector<u32> masks(h);
	// return rec(w, h, shapes, masks, cnts, accumulate(all(cnts), 0), 0, 0);
}

int main() {
	vector<Shape> shapes;
	int ans = 0;
	string s;
	vector<string> cur_shape;
	while (cin >> s) {
		if (s.back() != ':') {
			cur_shape.push_back(s);
		} else {
			if (!cur_shape.empty()) {
				shapes.push_back(Shape::from_str(cur_shape));
				cur_shape = {};
			}
			if (int x_idx = s.find('x'); x_idx != (int)string::npos) {
				vector<int> cnts(shapes.size());
				for (auto& x : cnts) {
					cin >> x;
				}
				int w = stoi(s.substr(0, x_idx));
				int h = stoi(s.substr(x_idx + 1));
				ans += can(w, h, shapes, cnts);
			} else {
				assert(s == to_string(shapes.size()) + ':');
			}
		}
	}
	cout << ans << "\n";

	return 0;
}
