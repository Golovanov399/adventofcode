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

int main() {
	int cur = 1;
	string row;
	auto upd_row = [&]() {
		row += (abs((int)row.size() - cur) <= 1) ? '#' : '.';
		if ((int)row.size() == 40) {
			cout << row << "\n";
			row = "";
		}
	};
	string type;
	while (cin >> type) {
		if (type == "noop") {
			upd_row();
		} else {
			upd_row();
			upd_row();
			cur += nxt();
		}
	}

	return 0;
}
