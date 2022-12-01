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
	vector<int> aa;
	int cur = 0;
	string s;
	while (getline(cin, s)) {
		if (s == "") {
			aa.push_back(cur);
			cur = 0;
			continue;
		}
		cur += stoi(s);
	}
	sort(all(aa));
	reverse(all(aa));
	cout << aa[0] + aa[1] + aa[2] << "\n";

	return 0;
}
