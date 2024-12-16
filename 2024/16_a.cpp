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

const int inf = 1e9;
const int dx[4] = {0, -1, 0, 1};
const int dy[4] = {1, 0, -1, 0};

int main() {
	vector<string> a;
	{
		string s;
		while (cin >> s) {
			a.push_back(s);
		}
	}
	const int n = a.size(), m = a[0].size();

	pair<int, int> start = {-1, -1};
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (a[i][j] == 'S') {
				start = {i, j};
			}
		}
	}
	vector<int> dp(n * m * 4, inf);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	auto upd = [&](int x, int y, int d, int val) {
		const int xyd = (x * m + y) * 4 + d;
		if (dp[xyd] > val) {
			dp[xyd] = val;
			pq.push({val, xyd});
		}
	};
	upd(start.first, start.second, 0, 0);

	while (!pq.empty()) {
		auto [val, xyd] = pq.top();
		pq.pop();
		if (dp[xyd] != val) {
			continue;
		}
		int d = xyd % 4;
		int y = xyd / 4 % m;
		int x = xyd / 4 / m;
		if (a[x][y] == 'E') {
			cout << val << "\n";
			break;
		}
		upd(x, y, (d + 1) % 4, val + 1000);
		upd(x, y, (d + 3) % 4, val + 1000);
		int nx = x + dx[d], ny = y + dy[d];
		if (a[nx][ny] != '#') {
			upd(nx, ny, d, val + 1);
		}
	}

	return 0;
}
