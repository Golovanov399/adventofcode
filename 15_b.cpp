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

const int N = 33'333'333;
int last[N];

int main() {
	memset(last, -1, sizeof(last));
	vector<int> a = {5,2,8,16,18,0,1};
	for (int i = 0; i < (int)a.size() - 1; ++i) {
		last[a[i]] = i;
	}
	while ((int)a.size() < 30'000'000) {
		int x = a.back();
		int cur = (int)a.size() - 1;
		if (last[x] == -1) {
			a.push_back(0);
		} else {
			a.push_back(cur - last[x]);
		}
		last[x] = cur;
	}
	cout << a.back() << "\n";

	return 0;
}
