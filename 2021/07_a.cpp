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
	int x = a[(int)a.size() / 2];
	int ans = 0;
	for (int y : a) {
		ans += abs(y - x);
	}
	cout << ans << "\n";

	return 0;
}
