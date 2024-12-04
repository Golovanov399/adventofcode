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
	vector<string> a;
	{
		string s;
		while (cin >> s) {
			a.push_back(s);
		}
	}
	int ans = 0;
	for (int i = 1; i < (int)a.size() - 1; ++i) {
		for (int j = 1; j < (int)a[i].size() - 1; ++j) {
			if (a[i][j] != 'A') {
				continue;
			}
			ans += (a[i - 1][j - 1] == 'M' || a[i + 1][j + 1] == 'M')
				&& (a[i - 1][j - 1] == 'S' || a[i + 1][j + 1] == 'S')
				&& (a[i - 1][j + 1] == 'M' || a[i + 1][j - 1] == 'M')
				&& (a[i - 1][j + 1] == 'S' || a[i + 1][j - 1] == 'S');
		}
	}
	cout << ans << "\n";

	return 0;
}
