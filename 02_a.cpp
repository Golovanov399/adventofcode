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
	int cnt = 0;
	for (int i = 0; i < 1000; ++i) {
		string cnts, let, pass;
		cin >> cnts >> let >> pass;
		char letter = let[0];
		int low = stoi(cnts.substr(0, cnts.find('-')));
		int high = stoi(cnts.substr(cnts.find('-') + 1));
		int actual = count(all(pass), letter);
		cnt += clamp(actual, low, high) == actual;
	}
	cout << cnt << "\n";

	return 0;
}
