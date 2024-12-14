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
	const int w = 101, h = 103;
	const int wait_time = 100;
	int cnt[2][2];
	memset(cnt, 0, sizeof(cnt));
	string s;
	while (cin >> s) {
		s = s.substr(2);
		int i = s.find(',');
		int y = stoi(s.substr(0, i));
		int x = stoi(s.substr(i + 1));
		cin >> s;
		s = s.substr(2);
		i = s.find(',');
		int dy = stoi(s.substr(0, i));
		int dx = stoi(s.substr(i + 1));
		dx = (dx % h + h) % h;
		dy = (dy % w + w) % w;

		x = (x + dx * wait_time) % h;
		y = (y + dy * wait_time) % w;
		// cerr << x << " " << y << "\n";
		if (x != h / 2 && y != w / 2) {
			cnt[x > h/2][y > w/2] += 1;
		}
	}
	cout << cnt[0][0] * cnt[0][1] * cnt[1][0] * cnt[1][1] << "\n";

	return 0;
}
