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
	const string s = "253149867";
	const int n = 1'000'000;
	vector<int> p(n + 1);
	vector<int> a(n);
	for (int i = 0; i < (int)s.length(); ++i) {
		a[i] = s[i] - '0';
	}
	iota((int)s.length() + all(a), (int)s.length() + 1);
	for (int i = 0; i < n; ++i) {
		p[a[i]] = a[(i + 1) % n];
	}
	int cur = a[0];
	for (int i = 0; i < 10'000'000; ++i) {
		vector<int> b;
		int v = cur;
		for (int j = 0; j < 3; ++j) {
			v = p[v];
			b.push_back(v);
		}
		v = p[v];
		p[cur] = v;
		v = cur;
		cur = p[cur];
		while (true) {
			v -= 1;
			if (v <= 0) {
				v = n;
			}
			if (find(all(b), v) == b.end()) {
				break;
			}
		}
		p[b.back()] = p[v];
		p[v] = b[0];
	}
	cerr << p[1] << " " << p[p[1]] << "\n";
	cout << p[1] * 1ll * p[p[1]] << "\n";

	return 0;
}
