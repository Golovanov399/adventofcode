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
		int t = 30;
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
		vector<int> perm(n - 1);
		iota(all(perm), 1);
		shuffle(all(perm), rr);
		int ans = get_score(perm);
		while (true) {
			bool ok = false;
			for (int i = 0; i < (int)perm.size(); ++i) {
				auto p = perm;
				p.erase(p.begin() + i);
				for (int j = 0; j < (int)perm.size(); ++j) {
					p.insert(p.begin() + j, perm[i]);
					if (auto s = get_score(p); s > ans) {
						ans = s;
						perm = p;
						ok = true;
						break;
					}
					p.erase(p.begin() + j);
				}
			}
			if (!ok) {
				break;
			}
		}
		return ans;
	};

	int ans = 0;
	for (int seed = 0; seed < 100; ++seed) {
		ans = max(ans, f(seed));
	}
	cout << ans << "\n";

	return 0;
}
