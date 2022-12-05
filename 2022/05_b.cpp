#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define itn int
#define make_unique(x) sort((x).begin(), (x).end()); (x).erase(unique((x).begin(), (x).end()), (x).end())

using namespace std;

inline int nxt() {
	int x;
	cin >> x;
	return x;
}

bool starts_with(string s, string t) {
	return s.length() >= t.length() && s.substr(0, t.length()) == t;
}

vector<string> split(string s) {
	vector<string> res = {""};
	for (char c : s) {
		if (isspace(c)) {
			res.push_back("");
		} else {
			res.back() += c;
		}
	}
	return res;
}

int main() {
	string s;
	int n = 0;
	vector<string> a;
	while (getline(cin, s)) {
		if (n == 0) {
			n = ((int)s.length() + 1) / 4;
			a.resize(n);
		}
		if (starts_with(s, " 1 ")) {
			for (auto& x : a) {
				reverse(all(x));
			}
		} else if (starts_with(s, "move")) {
			auto tkns = split(s);
			int c = stoi(tkns[1]), f = stoi(tkns[3]) - 1, t = stoi(tkns[5]) - 1;
			c = min(c, (int)a[f].length());
			auto str = a[f].substr((int)a[f].size() - c);
			a[f] = a[f].substr(0, (int)a[f].length() - c);
			// reverse(all(str));
			a[t] += str;
		} else if (s.find('[') != string::npos) {
			for (int i = 0; i < n; ++i) {
				if (isalpha(s[4 * i + 1])) {
					a[i] += s[4 * i + 1];
				}
			}
		}
	}

	string ans = "";
	for (auto x : a) {
		ans += x.back();
	}
	cout << ans << "\n";

	return 0;
}
