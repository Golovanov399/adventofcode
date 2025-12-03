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

const int K = 12;
const auto p10 = []() {
	vector<long long> p10(K + 1, 1);
	for (int i = 1; i <= K; ++i) {
		p10[i] = p10[i - 1] * 10;
	}
	return p10;
}();

long long get_max(string s) {
	vector<long long> mx(K + 1, -1);
	mx[0] = 0;
	for (int i = (int)s.length() - 1; i >= 0; --i) {
		for (int j = K; j > 0; --j) {
			if (mx[j - 1] > -1) {
				mx[j] = max(mx[j], mx[j - 1] + p10[j - 1] * (s[i] - '0'));
			}
		}
	}
	return mx[K];
}

int main() {
	auto lines = read_lines();
	long long ans = 0;
	for (auto s : lines) {
		ans += get_max(s);
	}
	cout << ans << "\n";

	return 0;
}
