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
	vector<long long> a;
	{
		long long x;
		while (cin >> x) {
			a.push_back(x);
		}
	}
	for (int i = 0; i < 25; ++i) {
		vector<long long> b;
		for (long long x : a) {
			if (x == 0) {
				b.push_back(1);
			} else if (to_string(x).size() % 2 == 0) {
				auto s = to_string(x);
				b.push_back(stoll(s.substr(0, s.size() / 2)));
				b.push_back(stoll(s.substr(s.size() / 2)));
			} else {
				b.push_back(x * 2024);
			}
		}
		a.swap(b);
	}
	cout << a.size() << "\n";

	return 0;
}
