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

struct Point {
	int x, y;
};

int main() {
	vector<Point> pts;
	string s;
	while (cin >> s) {
		int i = s.find(',');
		int x = stoi(s.substr(0, i));
		int y = stoi(s.substr(i + 1));
		pts.push_back({x, y});
	}
	long long ans = 0;
	for (auto p : pts) {
		for (auto q : pts) {
			ans = max(ans, 1ll * (abs(p.x - q.x) + 1) * (abs(p.y - q.y) + 1));
		}
	}
	cout << ans << "\n";

	return 0;
}
