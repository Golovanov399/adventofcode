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
	if (c == ')') {
		return 3;
	} else if (c == ']') {
		return 57;
	} else if (c == '}') {
		return 1197;
	} else if (c == '>') {
		return 25137;
	} else {
		assert(false);
	}
}

int main() {
	string s;
	int ans = 0;
	while (cin >> s) {
		vector<char> st;
		for (char c : s) {
			if (is_open(c)) {
				st.push_back(c);
			} else if (st.empty() || !is_pair(c, st.back())) {
				ans += f(c);
				break;
			} else {
				st.pop_back();
			}
		}
	}
	cout << ans << "\n";

	return 0;
}
