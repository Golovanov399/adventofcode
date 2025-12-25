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


using ld = double;
const ld eps = 1e-9;

struct LP {
	vector<vector<ld>> D;
	vector<int> basis;
	vector<int> nonbasis;
	vector<ld> target;
	int m, n;

	LP(vector<vector<ld>> a, vector<ld> b, vector<ld> c, bool dual = false) {
		// Ax <= b
		// x >= 0
		// cx -> max

		// dual problem looks like:
		// -A^Ty <= -c
		// y >= 0
		// -by -> max
		if (dual) {
			vector<vector<ld>> at(a[0].size(), vector<ld>(a.size(), 0));
			for (int i = 0; i < (int)a.size(); ++i) {
				for (int j = 0; j < (int)a[i].size(); ++j) {
					at[j][i] = -a[i][j];
				}
			}
			a = at;
			b.swap(c);
			for (auto& x : c) {
				x = -x;
			}
			for (auto& x : b) {
				x = -x;
			}
		}

		target = c;

		n = c.size();
		m = a.size();
		nonbasis.resize(n + 1);
		basis.resize(m);
		iota(all(nonbasis), 0);
		iota(all(basis), n);
		nonbasis[n] = -1;
		D = vector<vector<ld>>(m + 2, vector<ld>(n + 2, 0));
		/***
		 * this matrix looks as follows:
		 * 
		 * /        |1| \
		 * |   -A   |1|b|
		 * |        |1| |
		 * |--------+-+-|
		 * |   c^T  | | |
		 * |--------+-+-|
		 * \    0   |-| /
		 * 
		 * and is meant to represent the following:
		 *   - the last but one variable must be zero, it is to find a feasible solution
		 *   - the i-th column is how the i-th nonbasis vector is represented by the basis ones,
		 *   and the lowest is what is the c function increase if we pick (0, 0, ..., 0, 1, 0, 0, ...) nonbasis
		 *   - also if we multiply this by vector (x_nonbasis, 1) we get the vector (x_basis, our cost function)? I guess
		 */
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				D[i][j] = -a[i][j];
			}
			D[i][n] = 1;
			D[i][n + 1] = b[i];
		}
		for (int i = 0; i < n; ++i) {
			D[m][i] = c[i];
		}
		D[m + 1][n] = -1;
	}

	void add_dual_constraint(vector<ld> a, ld b) {
		// cerr << nonbasis << " " << basis << " " << D << "\n";
		auto add_number = [&](vector<ld>& vec, ld z) {
			auto x = vec.back();
			vec.pop_back();
			vec.push_back(z);
			vec.push_back(x);
		};
		// in dual language this means "add a new variable, initially zero"
		// we also change the target function, adding there -b
		// aaand we change matrix -A, adding there a
		for (int i = 0; i < m + 2; ++i) {
			add_number(D[i], 0);
		}
		for (auto& x : nonbasis) {
			if (x >= n) {
				++x;
			}
		}
		for (auto& x : basis) {
			if (x >= n) {
				++x;
			}
		}
		nonbasis.push_back(n++);
		D[m][n] = -b;
		for (int j = 0; j < n; ++j) {
			if (nonbasis[j] >= n) {
				for (int i = 0; i < m; ++i) {
					D[i][n] -= a[nonbasis[j] - n] * D[i][j];
				}
				// D[m][n] -= D[m][j];
			}
		}
		// for (int i = 0; i < m; ++i) {
		// 	if (basis[i] >= n) {
		// 		D[i][n] -= a[basis[i] - n];
		// 	}
		// }
		// for (int i = 0; i < n; ++i) {
		// 	if (nonbasis[i] >= n) {
		// 		ld k = a[nonbasis[i] - n];
		// 		for (int j = 0; j < m; ++j) {
		// 			D[j][n] -= k * D[j][i];
		// 		}
		// 	}
		// }
		for (int i = 0; i < m; ++i) {
			if (basis[i] > -1 && basis[i] < n) {
				D[m][n] += target[basis[i]] * D[i][n];
			}
		}
		// for (int i = 0; i < n - 1; ++i) {
		// 	D[m][n] -= target[i] * a[i];
		// }
		target.push_back(-b);
		// cerr << nonbasis << " " << basis << " " << D << "\n";
	}

	bool solve() {
		int bi = -1;
		for (int i = 0; i < m; ++i) {
			if (bi == -1 || D[i][n + 1] < D[bi][n + 1]) {
				bi = i;
			}
		}
		assert(bi != -1);
		if (D[bi][n + 1] < -eps) {
			pivot(bi, n);

			if (!simplex(1) || D[m + 1][n + 1] < -eps) {
				return false;
			}
		}

		return simplex(2);
	}

	void pivot(int bi, int nbi) {
		ld q = 1 / -D[bi][nbi];
		D[bi][nbi] = -1;
		for (auto& x : D[bi]) {
			x *= q;
		}
		for (int i = 0; i < (int)D.size(); ++i) {
			if (i == bi) {
				continue;
			}
			ld coef = D[i][nbi];
			D[i][nbi] = 0;
			for (int j = 0; j < (int)D[i].size(); ++j) {
				D[i][j] += coef * D[bi][j];
			}
		}
		swap(basis[bi], nonbasis[nbi]);
	}

	bool simplex(int phase) {
		// phase = 1 means we want a feasible solution
		// phase = 2 means we already have one and want to find the optimal one
		const int n = D[0].size();
		const int m = (int)D.size() - (phase == 2);

		while (true) {
			// choose some nonbasis index, so that c * x increases
			int nbi = -1;
			for (int i = 0; i < n - 1; ++i) {
				if (nonbasis[i] == -1 && phase == 2) {
					continue;
				}
				if (nbi == -1 || D[m - 1][i] > D[m - 1][nbi]) {
					nbi = i;
				}
			}
			if (D[m - 1][nbi] < eps) {
				if (phase == 1) {
					return false;
				}
				break;
			}

			int bi = -1;
			ld curval = 0;
			for (int i = 0; i < m - (phase == 1) - 1; ++i) {
				if (D[i][nbi] > -eps) {
					continue;
				}
				if (auto newval = D[i][n - 1] / -D[i][nbi]; bi == -1 || newval < curval || (abs(newval - curval) < eps && basis[i] < basis[bi])) {
					bi = i;
					curval = newval;
				}
			}
			if (bi == -1) {
				return false;
			}

			pivot(bi, nbi);
			if (nonbasis[nbi] == -1 && phase == 1) {
				return true;
			}
		}

		return true;
	}

	ld score() const {
		return D[m][n + 1];
	}

	vector<ld> get_x() const {
		vector<ld> res(n);
		for (int i = 0; i < m; ++i) {
			if (basis[i] < n) {
				res[basis[i]] = D[i][n + 1];
			}
		}
		return res;
	}

	vector<ld> get_dual_x() const {
		vector<ld> res(m);
		for (int i = 0; i < n + 1; ++i) {
			if (nonbasis[i] >= n) {
				res[nonbasis[i] - n] = -D[m][i];
			}
		}
		return res;
	}
};

struct ILP {
	const int m, n;
	pair<int, vector<int>> opt;
	vector<vector<ld>> a;
	vector<ld> b, c;
	vector<int> ci_;
	// mutex mut;

	ILP(vector<vector<int>> ai, vector<int> bi, vector<int> ci): m(ai.size()), n(ci.size()), ci_(ci) {
		a = vector(m, vector<ld>(n, 0));
		b = vector<ld>(m);
		c = vector<ld>(n);
		for (int i = 0; i < m; ++i) {
			copy(all(ai[i]), a[i].begin());
			b[i] = bi[i];
		}
		opt.first = -1e9;
		copy(all(ci), c.begin());

		// for (int i = 0; i < n; ++i) {
		// 	cout << "var x" << i << " >= 0, integer;\n";
		// }
		// auto output_row = [&](const vector<int>& vec) {
		// 	bool fp = true;
		// 	for (int i = 0; i < n; ++i) {
		// 		if (!vec[i]) {
		// 			continue;
		// 		}
		// 		if (!fp || vec[i] < 0) {
		// 			cout << " " << (vec[i] > 0 ? '+' : '-') << " " << abs(vec[i]);
		// 		} else {
		// 			cout << vec[i];
		// 		}
		// 		fp = false;
		// 		cout << " * x" << i;
		// 	}
		// };
		// cout << "maximize z: ";
		// output_row(ci);
		// cout << ";\n";
		// for (int i = 0; i < m; ++i) {
		// 	if (count(all(ai[i]), 0) == n) {
		// 		assert(bi[i] == 0);
		// 		continue;
		// 	}
		// 	cout << "subject to in" << i << ": ";
		// 	output_row(ai[i]);
		// 	cout << " <= " << bi[i] << ";\n";
		// }
		// exit(0);
	}

	void rec(LP lp) {
		// LP lp(a, b, c, true);
		if (!lp.solve()) {
			return;
		}
		if (-lp.score() < opt.first + 1 - eps) {
			return;
		}
		auto x = lp.get_dual_x();
		pair<ld, int> to_branch = {eps, -1};
		for (int i = 0; i < n; ++i) {
			to_branch = max(to_branch, {abs(x[i] - round(x[i])), i});
			if (to_branch.second > -1) {
				break;
			}
		}
		if (to_branch.second == -1) {
			vector<int> xi(n);
			for (int i = 0; i < n; ++i) {
				xi[i] = round(x[i]);
			}
			pair<int, vector<int>> cand{score(xi), xi};
			// lock_guard<mutex> guard(mut);
			if (cand.first > opt.first) {
				cerr << "new score: " << cand.first << "\n";
				opt = cand;
			}
			return;
		}
		const int i = to_branch.second;
		{
			auto nlp = lp;
			vector<ld> row(n, 0);
			row[i] = -1;
			nlp.add_dual_constraint(row, -ceil(x[i]));
			rec(nlp);
		}
		{
			auto& nlp = lp;
			vector<ld> row(n, 0);
			row[i] = 1;
			nlp.add_dual_constraint(row, floor(x[i]));
			rec(nlp);
		}
	}

	int score(const vector<int>& x) {
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			ans += ci_[i] * x[i];
		}
		return ans;
	};

	pair<int, vector<int>> solve() {
		LP lp(a, b, c, true);
		rec(lp);
		return opt;
	}
};

int main() {
	string s;
	int ans = 0;
	while (cin >> s) {
		const int n = s.length() - 2;
		vector<vector<int>> a(n);
		while (true) {
			cin >> s;
			if (s[0] == '{') {
				break;
			}
			for (auto& v : a) {
				v.push_back(0);
			}
			s = s.substr(1);
			s.pop_back();
			int i = 0;
			while (i < (int)s.length()) {
				int j = i;
				while (j < (int)s.length() && s[j] != ',') {
					++j;
				}
				a[stoi(s.substr(i, j - i))].back() = 1;
				i = j + 1;
			}
		}
		vector<int> need;
		s = s.substr(1);
		s.pop_back();
		{
			int i = 0;
			while (i < (int)s.length()) {
				int j = i;
				while (j < (int)s.length() && s[j] != ',') {
					++j;
				}
				need.push_back(stoi(s.substr(i, j - i)));
				i = j + 1;
			}
		}
		for (int i = 0; i < n; ++i) {
			auto v = a[i];
			a.push_back(v);
			for (auto& x : a.back()) {
				x = -x;
			}
			need.push_back(-need[i]);
		}
		auto [cnt, cnts] = ILP(a, need, vector(a[0].size(), -1)).solve();
		ans -= cnt;
	}
	cout << ans << "\n";

	return 0;
}
