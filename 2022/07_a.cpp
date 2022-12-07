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

struct Dir {
	Dir* par;
	map<string, Dir*> sons;
	long long sz;

	Dir(): par(nullptr), sz(0) {}
	explicit Dir(Dir* p): par(p), sz(0) {}
};

int main() {
	Dir* root = new Dir();
	auto cur = root;
	string s;
	while (getline(cin, s)) {
		auto cmd = split(s);
		if (cmd[0] == "$") {
			if (cmd[1] == "cd") {
				assert((int)cmd.size() == 3);
				if (cmd[2] == "/") {
					cur = root;
				} else if (cmd[2] == "..") {
					if (cur->par) {
						cur = cur->par;
					}
				} else {
					if (!cur->sons.contains(cmd[2])) {
						cur->sons[cmd[2]] = new Dir(cur);
					}
					cur = cur->sons.at(cmd[2]);
				}
			} else {
				assert((int)cmd.size() == 2);
				cur->sz = 0;
			}
		} else {
			assert((int)cmd.size() == 2);
			string name = cmd[1];
			if (cmd[0] == "dir") {
				if (!cur->sons.contains(name)) {
					cur->sons[name] = new Dir(cur);
				}
			} else {
				cur->sz += stoll(cmd[0]);
			}
		}
	}

	long long ans = 0;
	function<void(Dir*)> rec = [&](Dir* v) {
		for (const auto& it : v->sons) {
			auto u = it.second;
			rec(u);
			v->sz += u->sz;
		}
		if (v->sz <= 100'000) {
			ans += v->sz;
		}
	};
	rec(root);
	cout << ans << "\n";

	return 0;
}
