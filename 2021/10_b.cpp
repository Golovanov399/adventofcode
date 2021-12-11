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

bool is_open(char c) {
	return string("([{<").find(c) != string::npos;
}

char is_pair(char c, char d) {
	return string("([{<").find(d) == string(")]}>").find(c);
}

int f(char c) {
	if (c == '(') {
		return 1;
	} else if (c == '[') {
		return 2;
	} else if (c == '{') {
		return 3;
	} else if (c == '<') {
		return 4;
	} else {
		assert(false);
	}
}

int main() {
	string s;
	vector<long long> ss;
	while (cin >> s) {
		vector<char> st;
		bool bad = false;
		for (char c : s) {
			if (is_open(c)) {
				st.push_back(c);
			} else if (st.empty() || !is_pair(c, st.back())) {
				bad = true;
				break;
			} else {
				st.pop_back();
			}
		}
		if (bad) {
			continue;
		}
		long long cur = 0;
		while (!st.empty()) {
			cur = cur * 5 + f(st.back());
			st.pop_back();
		}
		ss.push_back(cur);
	}
	sort(all(ss));
	cout << ss[ss.size()/2] << "\n";

	return 0;
}
