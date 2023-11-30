#include <bits/stdc++.h>
#include "aoc.h"

#define all(x) (x).begin(), (x).end()

using namespace std;

inline int nxt() {
	int x;
	cin >> x;
	return x;
}

int best(List<String> a, bool mcb) {
	const int sz = a[0].length();
	return range(sz).fold(a, [&](auto list, int i) {
		if (list.size() == 1) {
			return list;
		}
		auto cnt = range(2).map([&](int c) { return list.count([&](auto s) { return s[i] == '0' + c; }); });
		const int bit = '0' + (cnt[0] <= cnt[1]);
		return list.filter([&](auto s) { return (s[i] == bit) == mcb; });
	})[0].reversed().with_index().sum_of([](const auto& iv) { return ((int)iv.value - '0') << iv.index; });
}

int main() {
	auto a = read_strings();
	cout << best(a, true) * best(a, false) << "\n";

	return 0;
}
