#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define itn int
#define make_unique(x) sort((x).begin(), (x).end()); (x).erase(unique((x).begin(), (x).end()), (x).end())

using namespace std;

inline int nxt() {
	int x;
	scanf("%d", &x);
	return x;
}

const int off = 50;
const int N = 2 * off + 1;

struct Range {
	int from, to;
};

array<Range, 3> parse(string s) {
	s += ',';
	array<Range, 3> res;
	for (auto& r : res) {
		int pos = s.find(',');
		auto t = s.substr(0, pos);
		s = s.substr(pos + 1);
		t = t.substr(2);
		pos = t.find("..");
		r.from = stoi(t.substr(0, pos));
		r.to = stoi(t.substr(pos + 2));
	}
	return res;
}

int state[N][N][N];

int main() {
	string type;
	string s;
	while (cin >> type >> s) {
		auto r = parse(s);
		int val = type == "on";
		for (int x = max(-off, r[0].from); x <= min(off, r[0].to); ++x) {
			for (int y = max(-off, r[1].from); y <= min(off, r[1].to); ++y) {
				for (int z = max(-off, r[2].from); z <= min(off, r[2].to); ++z) {
					state[x + off][y + off][z + off] = val;
				}
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			ans += accumulate(state[i][j], state[i][j] + N, 0);
		}
	}
	cout << ans << "\n";

	return 0;
}
