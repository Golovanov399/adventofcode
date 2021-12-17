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

int main() {
	int mx, Mx, my, My;
	{
		string s;
		cin >> s;
		cin >> s;
		cin >> s;
		s = s.substr(2);
		s.pop_back();
		mx = stoi(s.substr(0, s.find('.')));
		Mx = stoi(s.substr(s.find('.') + 2));
		cin >> s;
		s = s.substr(2);
		my = stoi(s.substr(0, s.find('.')));
		My = stoi(s.substr(s.find('.') + 2));
	}
	cerr << mx << " " << Mx << " " << my << " " << My << "\n";

	int ans = 0;
	for (int x = 1; x <= Mx; ++x) {
		for (int y = my; y <= -my; ++y) {
			bool ok = false;
			int dx = x, dy = y;
			int cx = 0, cy = 0;
			while (cx <= Mx && cy >= my) {
				cx += dx;
				cy += dy;
				ok |= clamp(cx, mx, Mx) == cx && clamp(cy, my, My) == cy;
				dx -= (dx < 0 ? -1 : dx > 0);
				dy -= 1;
			}

			if (ok) {
				++ans;
			}
		}
	}
	cout << ans << "\n";

	return 0;
}
