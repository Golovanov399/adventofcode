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
	vector<pair<int, int>> prs;
	{
		string s;
		while (cin >> s) {
			int i = s.find(',');
			int x = stoi(s.substr(0, i));
			int y = stoi(s.substr(i + 1));
			prs.push_back({x, y});
		}
	}
	int le = 0, ri = (int)prs.size() + 1;
	while (ri > le + 1) {
		int cnt = (le + ri) / 2;
		memset(d, -1, sizeof(d));
		for (int it = 0; it < cnt; ++it) {
			auto [x, y] = prs[it];
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
		(d[N - 1][N - 1] == -1 ? ri : le) = cnt;
	}
	auto [x, y] = prs[le];
	cout << x << "," << y << "\n";

	return 0;
}
