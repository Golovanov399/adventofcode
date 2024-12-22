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

u32 f(u32 x) {
	x = (x ^ (x << 6)) & 0xffffff;
	x = (x ^ (x >> 5)) & 0xffffff;
	x = (x ^ (x << 11)) & 0xffffff;
	return x;
}

int main() {
	uint64_t ans = 0;
	uint32_t cur;
	while (cin >> cur) {
		for (int i = 0; i < 2000; ++i) {
			cur = f(cur);
		}
		ans += cur;
	}
	cout << ans << "\n";

	return 0;
}
