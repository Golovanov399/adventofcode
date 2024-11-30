#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

// g++ -DLOCAL -std=c++20 -g -O0 -D_GLIBCXX_DEBUG -Wall -Wextra -x c++-header aoc.h -o ~/misc/precompiled-headers/Debug/aoc.h.gch
// g++ -DLOCAL -std=c++20 -O2 -Wno-unused-result -x c++-header aoc.h -o ~/misc/precompiled-headers/Release/aoc.h.gch

#define all(x) (x).begin(), (x).end()

using namespace std;

template <typename T>
struct IndexedValue {
	int index;
	T value;

	weak_ordering operator <=>(const IndexedValue& ot) const {
		if (auto cmp = (value <=> ot.value); cmp != weak_ordering::equivalent) {
			return cmp;
		}
		return index <=> ot.index;
	}
};

template <typename T>
struct List {
	vector<T> a;

	List(const vector<T>& vec): a(vec) {}

	List<T> filter(auto pred) const {
		vector<T> res;
		for (const auto& x : a) {
			if (pred(x)) {
				res.push_back(x);
			}
		}
		return res;
	}

	auto map(auto func) const {
		using S = decltype(func(declval<T>()));
		vector<S> res;
		for (const auto& x : a) {
			res.push_back(func(x));
		}
		return List<S>(res);
	}

	void for_each(auto func) const {
		for (const auto& x : a) {
			func(x);
		}
	}

	List<List<T>> windowed(int sz) const {
		vector<List<T>> res;
		for (int i = 0; i + sz <= size(); ++i) {
			res.emplace_back(vector(a.begin() + i, a.begin() + i + sz));
		}
		return res;
	}

	template <typename S>
	List<pair<T, S>> zip(const List<S>& ot) const {
		vector<pair<T, S>> res;
		for (int i = 0; i < size() && i < ot.size(); ++i) {
			res.push_back({a[i], ot[i]});
		}
		return res;
	}

	List<pair<T, T>> zip_with_next() const {
		vector<pair<T, T>> res;
		for (int i = 0; i + 1 < size(); ++i) {
			res.push_back({a[i], a[i + 1]});
		}
		return res;
	}

	List<T> reversed() const {
		return vector(a.rbegin(), a.rend());
	}

	List<T> sorted() const {
		List<T> res = a;
		sort(all(res.a));
		return res;
	}

	List<IndexedValue<T>> with_index() const {
		vector<IndexedValue<T>> res(size());
		for (int i = 0; i < size(); ++i) {
			res[i] = {i, a[i]};
		}
		return res;
	}

	template <typename S>
	S fold(const S& initial, auto func) const {
		S res = initial;
		for (const auto& x : a) {
			res = func(res, x);
		}
		return res;
	}

	int count(auto pred) const {
		int ans = 0;
		for (const auto& x : a) {
			ans += !!pred(x);
		}
		return ans;
	}

	bool empty() const {
		return a.empty();
	}

	T sum() const {
		return accumulate(all(a), T{});
	}

	auto sum_of(auto func) const {
		decltype(func(declval<T>())) res{};
		for (const auto& x : a) {
			res += func(x);
		}
		return res;
	}

	int size() const {
		return a.size();
	}

	const T& operator [](int i) const {
		return a[i];
	}

	T& operator [](int i) {
		return a[i];
	}
};

struct String {
	string s;

	String(const string& t): s(t) {}

	List<String> split(char c = ' ') const {
		vector<String> res;
		int cur = 0;
		for (int i = 0; i < length(); ++i) {
			if (s[i] == c) {
				res.emplace_back(s.substr(cur, i - cur));
				cur = i;
			}
		}
		res.emplace_back(s.substr(cur));
		return res;
	}

	List<String> split(string delim) const {
		vector<String> res;
		int cur = 0;
		for (int i = 0; i + (int)delim.length() <= length(); ++i) {
			if (s.substr(i, delim.length()) == delim) {
				res.emplace_back(s.substr(cur, i - cur));
				cur = (i += delim.length());
			}
		}
		res.emplace_back(s.substr(cur));
		return res;
	}

	String reversed() const {
		return string(s.rbegin(), s.rend());
	}

	List<IndexedValue<char>> with_index() const {
		vector<IndexedValue<char>> res(length());
		for (int i = 0; i < length(); ++i) {
			res[i] = {i, s[i]};
		}
		return res;
	}


	int to_int() const {
		return stoi(s);
	}

	int to_long() const {
		return stoll(s);
	}

	int length() const {
		return s.length();
	}

	char operator [](int i) const {
		return s[i];
	}

	char& operator [](int i) {
		return s[i];
	}

	bool operator ==(const string& ot) const {
		return s == ot;
	}

	weak_ordering operator <=>(const string& ot) const {
		return s <=> ot;
	}
};

List<int> range(int n) {
	vector<int> a(n);
	iota(all(a), 0);
	return a;
}

List<int> range(int from, int to) {
	// [from, to)
	vector<int> a(to - from);
	iota(all(a), from);
	return a;
}

List<int> read_ints() {
	vector<int> res;
	int x;
	while (cin >> x) {
		res.push_back(x);
	}
	return res;
}

List<String> read_strings() {
	vector<String> res;
	string s;
	while (getline(cin, s)) {
		res.emplace_back(s);
	}
	return res;
}

#undef all