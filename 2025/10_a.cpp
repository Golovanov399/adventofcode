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

const int inf = 1e9;
const double eps = 1e-9;

struct Sol {
	vector<vector<double>> mat;
	vector<vector<double>> rhs;

	optional<vector<double>> solve(const vector<double>& b) const {
		const int n = b.size();
		vector<double> res(mat[0].size());
		for (int i = (int)mat.size() - 1; i >= 0; --i) {
			double s = 0;
			for (int j = 0; j < n; ++j) {
				s += rhs[i][j] * b[j];
			}
			int fst = 0;
			while (abs(mat[i][fst]) < eps) {
				++fst;
			}
			for (int j = fst + 1; j < (int)mat[i].size(); ++j) {
				s -= res[j] * mat[i][j];
			}
			res[fst] = s / mat[i][fst];
		}
		for (int i = (int)mat.size(); i < n; ++i) {
			double s = 0;
			for (int j = 0; j < n; ++j) {
				s += rhs[i][j] * b[j];
			}
			if (abs(s) > eps) {
				return nullopt;
			}
		}
		return res;
	}
};

Sol gauss(vector<vector<double>> a) {
	if (a.empty()) {
		return {};
	}
	const int n = a.size();
	const int m = a[0].size();
	vector<vector<double>> rhs(n, vector<double>(n, 0));
	for (int i = 0; i < n; ++i) {
		rhs[i][i] = 1;
	}
	int row = 0;
	for (int j = 0; j < m && row < n; ++j) {
		if (abs(a[row][j]) < eps) {
			int i = row + 1;
			while (i < n && abs(a[i][j]) < eps) {
				++i;
			}
			if (i == n) {
				continue;
			}
			a[i].swap(a[row]);
			rhs[i].swap(rhs[row]);
		}
		for (int i = row + 1; i < n; ++i) {
			double k = a[i][j] / a[row][j];
			for (int l = j; l < m; ++l) {
				a[i][l] -= a[row][l] * k;
			}
			for (int l = 0; l < n; ++l) {
				rhs[i][l] -= rhs[row][l] * k;
			}
		}
		++row;
	}
	a.resize(row);
	return {a, rhs};
}

int main() {
	string s;
	int ans = 0;
	while (cin >> s) {
		const int n = s.length() - 2;
		vector<vector<int>> a;
		while (true) {
			cin >> s;
			if (s[0] == '{') {
				break;
			}
			a.emplace_back(n);
			s = s.substr(1);
			s.pop_back();
			int i = 0;
			while (i < (int)s.length()) {
				int j = i;
				while (j < (int)s.length() && s[j] != ',') {
					++j;
				}
				a.back()[stoi(s.substr(i, j - i))] = 1;
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

		if (all_of(all(need), [](int x) { return x == 0; })) {
			continue;
		}

		sort(all(a), [&](const auto& p, const auto& q) {
			return accumulate(all(p), 0) < accumulate(all(q), 0);
		});

		const int sz = a.size();
		vector<Sol> sols(1 << sz);
		int lin_indep_mask = 0;
		for (int mask = 0; mask < (1 << sz); ++mask) {
			vector<vector<double>> mat(n);
			for (int i = 0; i < sz; ++i) {
				if (mask & (1 << i)) {
					for (int j = 0; j < n; ++j) {
						mat[j].push_back(a[i][j]);
					}
				}
			}
			sols[mask] = gauss(mat);
			if (__builtin_popcount(mask) == sols[mask].mat.size() && __builtin_popcount(mask) > __builtin_popcount(lin_indep_mask)) {
				lin_indep_mask = mask;
			}
		}
		vector<int> ids;
		for (int i = 0; i < sz; ++i) {
			if (!(lin_indep_mask & (1 << i))) {
				ids.push_back(i);
			}
		}
		auto sol = sols[lin_indep_mask];
		int tmp = inf;
		function<void(vector<int>, int, int)> rec = [&](vector<int> nd, int i, int cur) {
			if (i == (int)ids.size()) {
				if (all_of(all(nd), [](int x) { return x == 0; })) {
					tmp = min(tmp, cur);
					return;
				}
				vector<double> dnd(all(nd));

				auto sold = sol.solve(dnd);
				if (!sold) {
					return;
				}
				vector<int> soli(__builtin_popcount(lin_indep_mask));
				for (int i = 0; i < (int)sold->size(); ++i) {
					soli[i] = round((*sold)[i]);
				}
				bool ok = true;
				for (int x : soli) {
					if (x < 0) {
						ok = false;
						break;
					}
				}
				if (!ok) {
					return;
				}
				vector<int> got(n);
				for (int i = 0, j = 0; i < sz; ++i) {
					if (!(lin_indep_mask & (1 << i))) {
						continue;
					}
					for (int k = 0; k < n; ++k) {
						got[k] += a[i][k] * soli[j];
					}
					++j;
				}
				if (got == nd) {
					tmp = min(tmp, cur + accumulate(all(soli), 0));
				}

				return;
			}
			while (true) {
				rec(nd, i + 1, cur);
				++cur;
				for (int j = 0; j < n; ++j) {
					nd[j] -= a[ids[i]][j];
					if (nd[j] < 0) {
						return;
					}
				}
			}
		};
		rec(need, 0, 0);
		ans += tmp;
		// for (int mask = 1; mask < (1 << sz); ++mask) {
		// 	vector<int> tot(n);
		// 	for (int i = 0; i < sz; ++i) {
		// 		if (mask & (1 << i)) {
		// 			for (int j = 0; j < n; ++j) {
		// 				tot[j] += a[i][j];
		// 			}
		// 		}
		// 	}
		// 	for (int m = 1;; ++m) {
		// 		vector<double> nd(all(need));
		// 		bool ok = true;
		// 		for (int i = 0; i < n; ++i) {
		// 			nd[i] -= tot[i] * m;
		// 			if (nd[i] < 0) {
		// 				ok = false;
		// 			}
		// 		}
		// 		if (!ok) {
		// 			break;
		// 		}
		// 		if (all_of(all(nd), [](int x) { return x == 0; })) {
		// 			tmp = min(tmp, m * __builtin_popcount(mask));
		// 			continue;
		// 		}
		// 		for (int sm = (mask - 1) & mask; sm; sm = (sm - 1) & mask) {
		// 			auto sold = sols[sm].solve(nd);
		// 			if (!sold) {
		// 				continue;
		// 			}
		// 			vector<int> soli(__builtin_popcount(sm));
		// 			for (int i = 0; i < (int)sold->size(); ++i) {
		// 				soli[i] = round((*sold)[i]);
		// 			}
		// 			bool ok = true;
		// 			for (int x : soli) {
		// 				if (x < 0) {
		// 					ok = false;
		// 					break;
		// 				}
		// 			}
		// 			if (!ok) {
		// 				continue;
		// 			}
		// 			vector<int> got(n);
		// 			for (int i = 0, j = 0; i < sz; ++i) {
		// 				if (!(sm & (1 << i))) {
		// 					continue;
		// 				}
		// 				for (int k = 0; k < n; ++k) {
		// 					got[k] += a[i][k] * soli[j];
		// 				}
		// 				++j;
		// 			}
		// 			for (int i = 0; i < n; ++i) {
		// 				got[i] += tot[i] * m;
		// 			}
		// 			if (got == need) {
		// 				tmp = min(tmp, m * __builtin_popcount(mask) + accumulate(all(soli), 0));
		// 			}
		// 		}
		// 	}
		// }
		// ans += tmp;
	}
	cout << ans << "\n";

	return 0;
}
