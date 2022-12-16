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

int sign(int x) {
	return x < 0 ? -1 : x > 0;
}

double get_time() {
	return std::chrono::system_clock::now().time_since_epoch().count() * 1e-9;
}

using ld = double;

int main() {
	map<string, vector<string>> to;
	map<string, int> score;
	{
		string s;
		while (getline(cin, s)) {
			auto spl = split(s, " ");
			string name = spl[1];
			spl[4].pop_back();
			score[name] = stoi(spl[4].substr(5));
			for (int i = 9; i < (int)spl.size() - 1; ++i) {
				spl[i].pop_back();
			}
			for (int i = 9; i < (int)spl.size(); ++i) {
				to[name].push_back(spl[i]);
			}
		}
	}

	vector<string> names;
	vector<int> scr;
	for (auto p : score) {
		names.push_back(p.first);
		scr.push_back(p.second);
	}

	const int n = names.size();
	vector<vector<int>> a(n);
	for (int i = 0; i < n; ++i) {
		for (auto t : to.at(names[i])) {
			a[i].push_back(lower_bound(all(names), t) - names.begin());
		}
	}
	vector<vector<int>> d(n, vector<int>(n, 1e9));
	for (int i = 0; i < n; ++i) {
		d[i][i] = 0;
		for (int j : a[i]) {
			d[i][j] = 1;
		}
	}
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
			}
		}
	}

	auto get_score = [&](const vector<int>& perm) {
		int t = 26;
		int v = 0;
		int ans = 0;
		for (int i : perm) {
			t -= d[v][i] + 1;
			if (t < 0) {
				break;
			}
			ans += scr[i] * t;
			v = i;
		}
		return ans;
	};

	auto f = [&](int seed) {
		mt19937 rr(seed);

		auto rand_double = [&]() {
			return (ld)rr() / decltype(rr)::max();
		};

		vector<int> perm(n - 1);
		iota(all(perm), 1);
		shuffle(all(perm), rr);
		vector<int> left, right;
		for (int x : perm) {
			if (rr() % 2) {
				left.push_back(x);
			} else {
				right.push_back(x);
			}
		}
		double start = get_time();
		const ld tmax = 1e2;
		const ld tmin = 1e-9;
		const ld max_time = 2;
		int ans = get_score(left) + get_score(right);
		while (true) {
			auto cur_time = (get_time() - start) / max_time;
			if (cur_time > 1) {
				break;
			}
			ld temp = tmax * pow(tmin / tmax, cur_time);

			auto nl = left, nr = right;
			int i = rr() % (nl.size() + nr.size());
			int x = -1;
			if (i < (int)nl.size()) {
				x = nl[i];
				nl.erase(nl.begin() + i);
			} else {
				x = nr[i - (int)nl.size()];
				nr.erase(nr.begin() + (i - (int)nl.size()));
			}
			int j = rr() % (nl.size() + nr.size() + 2);
			if (j <= (int)nl.size()) {
				nl.insert(nl.begin() + j, x);
			} else {
				j -= (int)nl.size() + 1;
				nr.insert(nr.begin() + j, x);
			}

			auto sc = get_score(nl) + get_score(nr);
			if (sc > ans || rand_double() < exp((sc - ans) / temp)) {
				ans = sc;
				// cerr << ans << ", ";
				left = nl;
				right = nr;
			}
		}
		return ans;
	};

	cout << f(265) << "\n";

	return 0;
}
