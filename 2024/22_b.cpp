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
	uint32_t cur;
	vector<int> ans(19 * 19 * 19 * 19);
	vector<int> used(19 * 19 * 19 * 19);
	int timer = 0;
	while (cin >> cur) {
		vector<int> dgs = {(int)cur % 10};
		for (int i = 0; i < 2000; ++i) {
			cur = f(cur);
			dgs.push_back((int)cur % 10);
		}
		++timer;
		int cr = 0;
		for (int i = 1; i < (int)dgs.size(); ++i) {
			cr = (cr * 19 + 9 + (dgs[i] - dgs[i - 1])) % used.size();
			if (i >= 4 && used[cr] < timer) {
				used[cr] = timer;
				ans[cr] += dgs[i];
			}
		}
	}
	cout << *max_element(all(ans)) << "\n";

	return 0;
}
