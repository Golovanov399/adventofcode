#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define itn int
#define make_unique(x) sort((x).begin(), (x).end()); (x).erase(unique((x).begin(), (x).end()), (x).end())

using namespace std;

inline int nxt() {
	int x;
	cin >> x;
	return x;
}

bool starts_with(string s, string t) {
	return s.length() >= t.length() && s.substr(0, t.length()) == t;
}

vector<string> split(string s, string by = " ") {
	vector<string> res = {""};
	for (int i = 0; i < (int)s.length(); ++i) {
		if (s.substr(i, by.length()) == by) {
			res.push_back("");
			i += (int)by.length() - 1;
		} else {
			res.back() += s[i];
		}
	}
	return res;
}

int sign(int x) {
	return x < 0 ? -1 : x > 0;
}

int main() {
	set<tuple<int, int, int>> S;
	int minx = INT_MAX, maxx = INT_MIN;
	int miny = INT_MAX, maxy = INT_MIN;
	int minz = INT_MAX, maxz = INT_MIN;
	{
		string s;
		while (cin >> s) {
			auto t = split(s, ",");
			int x = stoi(t[0]);
			int y = stoi(t[1]);
			int z = stoi(t[2]);
			S.insert({x, y, z});

			minx = min(minx, x);
			miny = min(miny, y);
			minz = min(minz, z);
			maxx = max(maxx, x);
			maxy = max(maxy, y);
			maxz = max(maxz, z);
		}
	}

	int cx = maxx - minx + 3;
	int cy = maxy - miny + 3;
	int cz = maxz - minz + 3;
	int offx = minx - 1;
	int offy = miny - 1;
	int offz = minz - 1;
	vector<vector<vector<char>>> used(cx, vector<vector<char>>(cy, vector<char>(cz, 0)));

	function<void(int, int, int)> dfs = [&](int x, int y, int z) {
		if (clamp(x, 0, cx - 1) != x || clamp(y, 0, cy - 1) != y || clamp(z, 0, cz - 1) != z) {
			return;
		}
		if (S.contains({offx + x, offy + y, offz + z})) {
			return;
		}
		if (used[x][y][z]) {
			return;
		}
		used[x][y][z] = 1;
		dfs(x - 1, y, z);
		dfs(x + 1, y, z);
		dfs(x, y - 1, z);
		dfs(x, y + 1, z);
		dfs(x, y, z - 1);
		dfs(x, y, z + 1);
	};
	dfs(0, 0, 0);

	int ans = 0;
	for (int x = 0; x < cx; ++x) {
		for (int y = 0; y < cy; ++y) {
			for (int z = 0; z < cz; ++z) {
				if (used[x][y][z]) {
					continue;
				}
				ans += used[x - 1][y][z];
				ans += used[x + 1][y][z];
				ans += used[x][y - 1][z];
				ans += used[x][y + 1][z];
				ans += used[x][y][z - 1];
				ans += used[x][y][z + 1];
			}
		}
	}
	cout << ans << "\n";

	return 0;
}
