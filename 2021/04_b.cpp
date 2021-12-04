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

const int n = 100;
int a[n][5][5];
bool win[n];

bool check(int idx) {
	for (int i = 0; i < 5; ++i) {
		if (all_of(a[idx][i], a[idx][i] + 5, [&](int x) { return x == -1; })) {
			return true;
		}
	}
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < i; ++j) {
			swap(a[idx][i][j], a[idx][j][i]);
		}
	}
	for (int i = 0; i < 5; ++i) {
		if (all_of(a[idx][i], a[idx][i] + 5, [&](int x) { return x == -1; })) {
			return true;
		}
	}
	return false;
}

int main() {
	vector<int> seq;
	{
		string s;
		cin >> s;
		while (s.find(',') != string::npos) {
			int idx = s.find(',');
			seq.push_back(stoi(s.substr(0, idx)));
			s = s.substr(idx + 1);
		}
		seq.push_back(stoi(s));
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 5; ++j) {
			for (int k = 0; k < 5; ++k) {
				cin >> a[i][j][k];
			}
		}
	}

	int rem = n;
	for (int x : seq) {
		for (int i = 0; i < n; ++i) {
			if (win[i]) {
				continue;
			}
			for (int j = 0; j < 5; ++j) {
				for (int k = 0; k < 5; ++k) {
					if (a[i][j][k] == x) {
						a[i][j][k] = -1;
					}
				}
			}
			if (check(i)) {
				--rem;
				win[i] = 1;
				if (rem == 0) {
					int tot = 0;
					for (int j = 0; j < 5; ++j) {
						for (int k = 0; k < 5; ++k) {
							if (a[i][j][k] > -1) {
								tot += a[i][j][k];
							}
						}
					}
					cout << tot * x << "\n";
					return 0;
				}
			}
		}
	}

	return 0;
}
