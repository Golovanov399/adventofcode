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
	string s;
	cin >> s;
	vector<int> a;
	while (s.find(',') != string::npos) {
		int pos = s.find(',');
		a.push_back(stoi(s.substr(0, pos)));
		s = s.substr(pos + 1);
	}
	a.push_back(stoi(s));
	sort(all(a));

	auto calc = [&](int y) {
		long long ans = 0;
		for (int x : a) {
			int z = abs(x - y);
			ans += z * (z + 1) / 2;
		}
		return ans;
	};
	int l = a[0], r = a.back();
	while (r > l + 2) {
		int m1 = (2 * l + r) / 3;
		int m2 = (l + 2 * r) / 3;
		if (calc(m1) > calc(m2)) {
			l = m1;
		} else {
			r = m2;
		}
	}
	long long ans = calc(l);
	for (int i = l; i <= r; ++i) {
		ans = min(ans, calc(i));
	}
	cout << ans << "\n";

	return 0;
}
