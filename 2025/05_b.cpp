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
	
	vector<pair<long long, int>> fresh;
	for (auto s : a) {
		if (s.empty()) {
			continue;
		}
		if (auto i = s.find('-'); i != string::npos) {
			auto l = stoll(s.substr(0, i));
			auto r = stoll(s.substr(i + 1));
			fresh.push_back({l, 1});
			fresh.push_back({r + 1, -1});
		}
	}
	long long ans = 0;
	sort(all(fresh));
	long long last = -1;
	int bal = 0;
	for (auto [x, i] : fresh) {
		if (bal) {
			ans += x - last;
		}
		last = x;
		bal += i;
	}
	cout << ans << "\n";

	return 0;
}
