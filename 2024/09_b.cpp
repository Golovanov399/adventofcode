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

bool rec(long long val, const vector<long long>& rhs, int i) {
	i -= 1;
	if (i == 0) {
		return val == rhs[0];
	}
	assert(rhs[i] > 0);
	if (rec(val - rhs[i], rhs, i)) {
		return true;
	}
	if (val < 0) {
		return false;
	}
	if (val % rhs[i] == 0 && rec(val / rhs[i], rhs, i)) {
		return true;
	}
	string s = to_string(val);
	string t = to_string(rhs[i]);
	if (val < rhs[i]) {
		return false;
	}
	if (s.length() > t.length() && s.substr(s.length() - t.length()) == t) {
		return rec(stoll(s.substr(0, s.length() - t.length())), rhs, i);
	} 
	return false;
}

int main() {
	string s;
	cin >> s;
	vector<pair<int, int>> blocks;
	for (int i = 0; i < (int)s.size(); i += 2) {
		if (i) {
			blocks.push_back({s[i - 1] - '0', -1});
		}
		blocks.push_back({s[i] - '0', i / 2});
	}
	for (int i = (int)blocks.size() - 1; i > 0; --i) {
		if (blocks[i].second == -1) {
			continue;
		}
		// for (auto [k, v] : blocks) {
		// 	cerr << string(k, v > -1 ? (char)('0' + v) : '.');
		// }
		// cerr << "\n";
		int j = 0;
		while (j < i && (blocks[j].second > -1 || blocks[j].first < blocks[i].first)) {
			++j;
		}
		if (j < i) {
			blocks[j].first -= blocks[i].first;
			blocks.insert(blocks.begin() + i + 1, {blocks[i].first, -1});
			rotate(blocks.begin() + j, blocks.begin() + i, blocks.begin() + i + 1);
		}
	}
	int cur = 0;
	long long ans = 0;
	for (int i = 0; i < (int)blocks.size(); ++i) {
		if (blocks[i].second > -1) {
			ans += 1ll * (cur + cur + blocks[i].first - 1) * blocks[i].first / 2 * blocks[i].second;
		}
		cur += blocks[i].first;
	}
	cout << ans << "\n";

	return 0;
}
