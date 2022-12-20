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
	vector<pair<int, int>> a;
	{
		int x;
		while (cin >> x) {
			int i = a.size();
			a.push_back({x, i});
		}
	}
	for (int i = 0; i < (int)a.size(); ++i) {
		int j = 0;
		while (a[j].second != i) {
			++j;
		}
		int k = a[j].first;
		while (k) {
			if (k < 0) {
				if (j > 0) {
					swap(a[j - 1], a[j]);
					--j;
				} else {
					swap(a[0], a.back());
					j = (int)a.size() - 1;
				}
				++k;
			} else {
				if (j < (int)a.size() - 1) {
					swap(a[j + 1], a[j]);
					++j;
				} else {
					swap(a[0], a.back());
					j = 0;
				}
				--k;
			}
		}
	}

	int i = 0;
	while (a[i].first) {
		++i;
	}
	int ans = 0;
	for (int k : {1000, 2000, 3000}) {
		ans += a[(i + k) % a.size()].first;
	}
	cout << ans << "\n";

	return 0;
}
