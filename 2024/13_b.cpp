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
	long long ans = 0;

	string s;
	while (cin >> s) {
		cin >> s;
		cin >> s;
		s.pop_back();
		s = s.substr(s.find('+') + 1);
		long long ax = stoi(s);
		cin >> s;
		s = s.substr(s.find('+') + 1);
		long long ay = stoi(s);

		cin >> s;
		cin >> s;
		cin >> s;
		s.pop_back();
		s = s.substr(s.find('+') + 1);
		long long bx = stoi(s);
		cin >> s;
		s = s.substr(s.find('+') + 1);
		long long by = stoi(s);

		cin >> s;
		cin >> s;
		s.pop_back();
		s = s.substr(s.find('=') + 1);
		long long x = 10000000000000ll + stoi(s);
		cin >> s;
		s = s.substr(s.find('=') + 1);
		long long y = 10000000000000ll + stoi(s);

		long long res = LLONG_MAX;
		for (int i = 0; i <= 100; ++i) {
			long long rx = x - ax * i, ry = y - ay * i;
			if (rx >= 0 && ry >= 0 && rx % bx == 0 && ry % by == 0 && rx / bx == ry / by) {
				res = min(res, 3 * i + (rx / bx));
			}
		}
		for (int i = 0; i <= 100; ++i) {
			long long rx = x - bx * i, ry = y - by * i;
			if (rx >= 0 && ry >= 0 && rx % ax == 0 && ry % ay == 0 && rx / ax == ry / ay) {
				res = min(res, i + 3 * (rx / ax));
			}
		}
		{
			long long det = ax * by - ay * bx;
			long long num1 = x * by - y * bx;
			long long num2 = ax * y - ay * x;
			if (det != 0 && num1 % det == 0 && num2 % det == 0) {
				res = min(res, num1 / det * 3 + num2 / det);
			}
		}

		if (res != LLONG_MAX) {
			ans += res;
		}
	}
	cout << ans << "\n";

	return 0;
}
