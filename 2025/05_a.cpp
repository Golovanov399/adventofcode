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
	auto a = read_lines();
	
	vector<pair<long long, long long>> fresh;
	int ans = 0;
	for (auto s : a) {
		if (s.empty()) {
			continue;
		}
		if (auto i = s.find('-'); i != string::npos) {
			auto l = stoll(s.substr(0, i));
			auto r = stoll(s.substr(i + 1));
			fresh.push_back({l, r});
		} else {
			long long x = stoll(s);
			bool ok = false;
			for (auto [l, r] : fresh) {
				if (l <= x && x <= r) {
					ok = true;
					break;
				}
			}
			ans += ok;
		}
	}
	cout << ans << "\n";

	return 0;
}
