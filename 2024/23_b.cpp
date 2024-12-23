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

int main() {
	map<string, set<string>> M;
	{
		string s;
		while (cin >> s) {
			int i = s.find('-');
			auto l = s.substr(0, i), r = s.substr(i + 1);
			M[l].insert(r);
			M[r].insert(l);
		}
	}

	vector<string> opt;
	auto rec = [&](auto self, vector<string> cur, vector<string> rem) -> void {
		if (cur.size() > opt.size()) {
			opt = cur;
			sort(all(opt));
			for (auto s : opt) {
				cerr << s;
			}
			cerr << "\n";
		}
		while (!rem.empty()) {
			auto s = rem.back();
			rem.pop_back();
			vector<string> nw;
			const auto& S = M[s];
			for (auto t : rem) {
				if (S.contains(t)) {
					nw.push_back(t);
				}
			}
			cur.push_back(s);
			self(self, cur, nw);
			cur.pop_back();
		}
	};

	vector<string> everything;
	for (const auto& p : M) {
		everything.push_back(p.first);
	}
	rec(rec, {}, everything);
	for (int i = 0; i < (int)opt.size(); ++i) {
		if (i) {
			cout << ",";
		}
		cout << opt[i];
	}
	cout << "\n";

	return 0;
}
