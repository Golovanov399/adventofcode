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

constexpr int N = 20201227;
int rem[N];

long long pw(long long a, long long b, long long mod) {
	long long res = 1;
	while (b) {
		if (b & 1ll) {
			res = res * a % mod;
		}
		b >>= 1;
		a = a * a % mod;
	}
	return res;
}

int main() {
	for (int i = 7, j = 1; i != 1; i = i * 7 % N, ++j) {
		rem[i] = j;
	}
	int a = nxt();
	int b = rem[nxt()];
	cout << pw(a, b, N) << "\n";

	return 0;
}
