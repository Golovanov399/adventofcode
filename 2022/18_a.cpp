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
	{
		string s;
		while (cin >> s) {
			auto t = split(s, ",");
			int x = stoi(t[0]);
			int y = stoi(t[1]);
			int z = stoi(t[2]);
			S.insert({x, y, z});
		}
	}

	int ans = 0;
	for (auto [x, y, z] : S) {
		ans += !S.contains({x - 1, y, z});
		ans += !S.contains({x + 1, y, z});
		ans += !S.contains({x, y - 1, z});
		ans += !S.contains({x, y + 1, z});
		ans += !S.contains({x, y, z - 1});
		ans += !S.contains({x, y, z + 1});
	}
	cout << ans << "\n";

	return 0;
}
