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
	vector<int> a = {5,2,8,16,18,0,1};
	while ((int)a.size() < 2020) {
		int i = (int)a.size() - 1;
		int j = i - 1 - (find(a.rbegin() + 1, a.rend(), a[i]) - a.rbegin() - 1);
		if (j < 0) {
			a.push_back(0);
		} else {
			a.push_back(i - j);
		}
	}
	cout << a.back() << "\n";

	return 0;
}
