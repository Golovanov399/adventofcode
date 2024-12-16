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
	pair<int, int> finish = {-1, -1};
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (a[i][j] == 'S') {
				start = {i, j};
			}
			if (a[i][j] == 'E') {
				finish = {i, j};
			}
		}
	}
	vector<int> dp(n * m * 4, inf);
	vector<vector<int>> prv(n * m * 4);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	auto upd = [&](int from, int x, int y, int d, int val) {
		const int xyd = (x * m + y) * 4 + d;
		if (dp[xyd] > val) {
			prv[xyd] = {from};
			dp[xyd] = val;
			pq.push({val, xyd});
		} else if (dp[xyd] == val) {
			prv[xyd].push_back(from);
		}
	};
	upd(-1, start.first, start.second, 0, 0);

	while (!pq.empty()) {
		auto [val, xyd] = pq.top();
		pq.pop();
		if (dp[xyd] != val) {
			continue;
		}
		int d = xyd % 4;
		int y = xyd / 4 % m;
		int x = xyd / 4 / m;
		upd(xyd, x, y, (d + 1) % 4, val + 1000);
		upd(xyd, x, y, (d + 3) % 4, val + 1000);
		int nx = x + dx[d], ny = y + dy[d];
		if (a[nx][ny] != '#') {
			upd(xyd, nx, ny, d, val + 1);
		}
	}

	set<int> best;
	set<int> was;
	{
		int res = inf;
		for (int i = 0; i < 4; ++i) {
			res = min(res, dp[(finish.first * m + finish.second) * 4 + i]);
		}
		for (int i = 0; i < 4; ++i) {
			int cand = (finish.first * m + finish.second) * 4 + i;
			if (res == dp[cand]) {
				best.insert(cand);
			}
		}
	}
	set<int> res;
	while (!best.empty()) {
		int v = *best.begin();
		best.erase(best.begin());
		was.insert(v);
		res.insert(v / 4);
		for (int x : prv[v]) {
			if (x != -1 && !was.contains(x)) {
				best.insert(x);
			}
		}
	}
	cout << res.size() << "\n";

	return 0;
}
