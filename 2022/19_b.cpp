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

template <class Fun>
class y_combinator_result {
	Fun fun_;
public:
	template<class T>
	explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

	template <class ...Args>
	decltype(auto) operator()(Args &&...args) {
		return fun_(std::ref(*this), std::forward<Args>(args)...);
	}
};

template <class Fun>
decltype(auto) y_combinator(Fun &&fun) {
	return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
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

template <typename T>
ostream& operator <<(ostream& ostr, const std::vector<T>& vec) {
	auto [pre, sep, post] = (&ostr == &cout) ? make_tuple("", " ", "") : make_tuple("[", ", ", "]");
	ostr << pre;
	bool fp = true;
	for (const auto& x : vec) {
		if (fp) {
			fp = false;
		} else {
			ostr << sep;
		}
		ostr << x;
	}
	return ostr << post;
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

const int T = 32;

int f(
		int ore_ore,
		int clay_ore,
		int obs_ore,
		int obs_clay,
		int geo_ore,
		int geo_obs
) {
	clock_t start = clock();

	int need[4][4];
	memset(need, 0, sizeof(need));
	need[0][0] = ore_ore;
	need[1][0] = clay_ore;
	need[2][0] = obs_ore;
	need[2][1] = obs_clay;
	need[3][0] = geo_ore;
	need[3][2] = geo_obs;

	int maxneed[4];
	memset(maxneed, 0, sizeof(maxneed));
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			maxneed[j] = max(maxneed[j], need[i][j]);
		}
	}
	maxneed[3] = 1e9;

	int have[4];
	int res[4];
	memset(have, 0, sizeof(have));
	memset(res, 0, sizeof(res));
	have[0] = 1;
	int ans = 0;

	auto rec = y_combinator([&](auto rec, int rem) {
		if (res[3] + have[3] * rem > ans) {
			ans = res[3] + have[3] * rem;
			cerr << "new score: " << ans << "\n";
		}
		if (rem == 0) {
			return;
		}

		for (int i = 3; i >= 0; --i) {
			if (have[i] >= maxneed[i]) {
				continue;
			}
			int need_time = 0;
			for (int j = 0; j <= i; ++j) {
				if (res[j] >= need[i][j]) {
					continue;
				}
				if (have[j] == 0) {
					need_time = 1e9;
					break;
				}
				need_time = max(need_time, (need[i][j] - res[j] + have[j] - 1) / have[j]);
			}
			if (need_time >= rem) {
				continue;
			}
			for (int j = 0; j < 4; ++j) {
				res[j] += have[j] * (need_time + 1) - need[i][j];
			}
			have[i] += 1;
			// cerr << string(T - rem, '.') << "buy " << i << "\n";
			rec(rem - need_time - 1);
			have[i] -= 1;
			for (int j = 0; j < 4; ++j) {
				res[j] -= have[j] * (need_time + 1) - need[i][j];
			}
		}
	});
	rec(T);
	cerr << ans << " [" << (clock() - start) / 1. / CLOCKS_PER_SEC << "]\n";
	return ans;
}

int main() {
	// LP lp({{1, 0}, {0, 1}}, {4, 4}, {1, 1}, true);
	// lp.solve();
	// cerr << -lp.score() << " ";
	// cerr << lp.get_dual_x() << "\n";
	// lp.add_dual_constraint({1, 2}, 9);
	// lp.solve();
	// cerr << -lp.score() << " ";
	// cerr << lp.get_dual_x() << "\n";
	// lp.add_dual_constraint({2, 1}, 9);
	// lp.solve();
	// cerr << -lp.score() << " ";
	// cerr << lp.get_dual_x() << "\n";

	// lp.add_dual_constraint({2, 1}, 9);
	// lp.solve();
	// cerr << lp.get_dual_x() << "\n";
	// cerr << lp.D << "\n";
	// cerr << lp.nonbasis << "\n";
	// cerr << lp.basis << "\n";
	// cerr << lp.get_x() << "\n";
	// cerr << lp.get_dual_x() << "\n";
	// return 0;

	long long ans = 1;
	string s;
	while (cin >> s) {
		assert(s == "Blueprint");
		cin >> s;
		s.pop_back();
		int id = stoi(s);
		for (auto need : split("Each ore robot costs 228")) {
			cin >> s;
			if (need != "228") {
				assert(s == need);
			}
		}
		int ore_ore = stoi(s);
		for (auto need : split("ore. Each clay robot costs 228")) {
			cin >> s;
			if (need != "228") {
				assert(s == need);
			}
		}
		int clay_ore = stoi(s);
		for (auto need : split("ore. Each obsidian robot costs 228")) {
			cin >> s;
			if (need != "228") {
				assert(s == need);
			}
		}
		int obs_ore = stoi(s);
		for (auto need : split("ore and 228")) {
			cin >> s;
			if (need != "228") {
				assert(s == need);
			}
		}
		int obs_clay = stoi(s);
		for (auto need : split("clay. Each geode robot costs 228")) {
			cin >> s;
			if (need != "228") {
				assert(s == need);
			}
		}
		int geo_ore = stoi(s);
		for (auto need : split("ore and 228")) {
			cin >> s;
			if (need != "228") {
				assert(s == need);
			}
		}
		int geo_obs = stoi(s);
		cin >> s;
		assert(s == "obsidian.");

		ans *= f(ore_ore, clay_ore, obs_ore, obs_clay, geo_ore, geo_obs);
		if (id == 3) {
			break;
		}
	}
	cout << ans << "\n";

	return 0;
}
