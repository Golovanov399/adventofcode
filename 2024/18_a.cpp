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

const int N = 71;
int d[N][N];

int main() {
	memset(d, -1, sizeof(d));
	for (int it = 0; it < 1024; ++it) {
		string s;
		cin >> s;
		int i = s.find(',');
		int x = stoi(s.substr(0, i));
		int y = stoi(s.substr(i + 1));
		d[x][y] = -2;
	}
	queue<pair<int, int>> q;
	q.push({0, 0});
	d[0][0] = 0;
	while (!q.empty()) {
		auto [x, y] = q.front();
		q.pop();
		for (int dx = -1; dx <= 1; ++dx) {
			for (int dy = -1; dy <= 1; ++dy) {
				if (abs(dx) + abs(dy) != 1) {
					continue;
				}
				int nx = x + dx, ny = y + dy;
				if (clamp(nx, 0, N - 1) == nx && clamp(ny, 0, N - 1) == ny && d[nx][ny] == -1) {
					d[nx][ny] = d[x][y] + 1;
					q.push({nx, ny});
				}
			}
		}
	}
	cout << d[N - 1][N - 1] << "\n";

	return 0;
}
