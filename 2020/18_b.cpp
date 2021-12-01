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

int ns(const string& s, int i) {
	while (i < (int)s.size() && s[i] != ' ') {
		++i;
	}
	return i;
}

long long oneop(long long l, long long r, char op) {
	return op == '+' ? l + r : l * r;
}

long long calc(string s);

long long ng(string s, int& i) {
	long long rhs = 0;;
	if (s[i] == '(') {
		int j = i + 1;
		int bal = 1;
		while (bal) {
			if (s[j] == '(') {
				++bal;
			} else if (s[j] == ')') {
				--bal;
			}
			++j;
		}
		rhs = calc(s.substr(i + 1, j - i - 2));
		i = j;
	} else {
		int j = ns(s, i);
		rhs = stoll(s.substr(i, j - i));
		i = j;
	}
	return rhs;
}

long long calc(string s) {
	int i = 0;
	vector<long long> tokens;
	vector<char> ops;
	tokens.push_back(ng(s, i));
	while (i < (int)s.size()) {
		ops.push_back(s[i + 1]);
		i += 3;
		tokens.push_back(ng(s, i));
	}
	for (int i = 0; i < (int)ops.size(); ++i) {
		if (ops[i] == '+') {
			tokens[i] += tokens[i + 1];
			tokens.erase(tokens.begin() + i + 1);
			ops.erase(ops.begin() + i);
			--i;
		}
	}
	for (int i = 0; i < (int)ops.size(); ++i) {
		if (ops[i] == '*') {
			tokens[i] *= tokens[i + 1];
			tokens.erase(tokens.begin() + i + 1);
			ops.erase(ops.begin() + i);
			--i;
		}
	}
	assert(ops.empty());
	return tokens[0];
}

int main() {
	long long ans = 0;
	string s;
	while (getline(cin, s)) {
		if (s.empty()) {
			break;
		}
		ans += calc(s);
	}
	cout << ans << "\n";

	return 0;
}
