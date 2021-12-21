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
	int p[2];
	int s[2] = {0, 0};
	{
		string st;
		cin >> st;
		cin >> st;
		cin >> st;
		cin >> st;
		cin >> p[0];
		cin >> st;
		cin >> st;
		cin >> st;
		cin >> st;
		cin >> p[1];
	}
	int cnt = 0;
	int d = 0;
	for (int i = 0; s[0] < 1000 && s[1] < 1000; i ^= 1) {
		cnt += 1;
		p[i] += 3 * d + 6;
		d += 3;
		p[i] %= 10;
		if (p[i] == 0) {
			p[i] = 10;
		}
		s[i] += p[i];
		// cerr << i + 1 << ": " << p[i] << " (" << s[i] << ")\n";
	}
	cout << min(s[0], s[1]) * 3 * cnt << "\n";

	return 0;
}
