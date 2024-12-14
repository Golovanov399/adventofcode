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

struct Guy {
	int x, y;
	int dx, dy;
};

int main() {
	const int w = 101, h = 103;
	vector<Guy> guys;
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

		guys.push_back({x, y, dx, dy});
	}
	int t = 0;
	while (t < 10000) {
		vector<string> a(h, string(w, ' '));
		for (const auto& g : guys) {
			a[g.x][g.y] = '#';
		}
		if (t % 103 == 461 % 103) {
			cout << t << ":\n";
			for (auto s : a) {
				cout << s << "\n";
			}
			cout << "\n";
		}
		for (auto& g : guys) {
			g.x = (g.x + g.dx) % h;
			g.y = (g.y + g.dy) % w;
		}
		++t;
	}
	cerr << t << "\n";

	return 0;
}
