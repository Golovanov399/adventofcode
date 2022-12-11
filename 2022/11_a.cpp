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

vector<string> split(string s, string by = " ") {
	vector<string> res = {""};
	for (int i = 0; i < (int)s.length(); ++i) {
		if (s.substr(i, by.length()) == by) {
			res.push_back("");
			i += (int)by.length() - 1;
		} else {
			res.back() += s[i];
		}
	}
	return res;
}

struct Monkey {
	vector<int> items;
	string op;
	int div_by;
	int to[2];
};

int f(string op, int x) {
	auto tkns = split(op, " ");
	for (auto& s : tkns) {
		if (s == "old") {
			s = to_string(x);
		}
	}
	for (int i = 0; i < (int)tkns.size(); ++i) {
		if (tkns[i] != "*") {
			continue;
		}
		int x = stoi(tkns[i - 1]);
		int y = stoi(tkns[i + 1]);
		tkns.erase(tkns.begin() + i);
		tkns.erase(tkns.begin() + i);
		tkns[i - 1] = to_string(x * y);
		i -= 1;
	}
	for (int i = 0; i < (int)tkns.size(); ++i) {
		if ((int)tkns[i].size() > 1 || isdigit(tkns[i][0])) {
			continue;
		}
		assert(tkns[i] == "+" || tkns[i] == "-");
		char c = tkns[i][0];
		int x = stoi(tkns[i - 1]);
		int y = stoi(tkns[i + 1]);
		tkns.erase(tkns.begin() + i);
		tkns.erase(tkns.begin() + i);
		tkns[i - 1] = to_string(c == '+' ? x + y : x - y);
		i -= 1;
	}
	assert((int)tkns.size() == 1);
	return stoi(tkns[0]);
}

int main() {
	vector<Monkey> a;
	{
		string s;
		while (getline(cin, s)) {
			if (s.empty()) {
				continue;
			}
			assert(s == "Monkey " + to_string(a.size()) + ":");
			a.push_back(Monkey());

			getline(cin, s);
			assert(starts_with(s, "  Starting items: "));
			s = s.substr(18);
			auto si = split(s, ", ");
			for (auto t : si) {
				a.back().items.push_back(stoi(t));
			}

			getline(cin, s);
			assert(starts_with(s, "  Operation: new = "));
			s = s.substr(19);
			a.back().op = s;

			getline(cin, s);
			assert(starts_with(s, "  Test: divisible by "));
			s = s.substr(21);
			a.back().div_by = stoi(s);

			for (int it : {1, 0}) {
				getline(cin, s);
				string req = "    If ";
				req += (it ? "true" : "false");
				req += ": throw to monkey ";
				assert(starts_with(s, req));
				s = s.substr(req.size());
				a.back().to[it] = stoi(s);
			}
		}
	}

	const int n = a.size();
	vector<int> cnt(n);
	vector<int> sum(n);

	for (int it = 0; it < 20; ++it) {
		for (int i = 0; i < n; ++i) {
			auto& mon = a[i];
			for (int x : mon.items) {
				cnt[i] += 1;
				sum[i] += x;
				// cerr << "Monkey " << i << " has item " << x << "\n";
				x = f(mon.op, x);
				// cerr << "Now it is " << x << "\n";
				assert(x >= 0);
				x /= 3;
					// cerr << "Test passed, monkey " << mon.to[1] << " acquires item " << x << "\n";
				a[mon.to[x % mon.div_by == 0]].items.push_back(x);
			}
			mon.items = {};
		}
		// for (auto mon : a) {
		// 	for (int x : mon.items) {
		// 		cerr << x << " ";
		// 	}
		// 	cerr << "\n";
		// }
		// cerr << "\n";
	}
	{
		auto vec = cnt;
		sort(all(vec));
		cout << vec[n - 2] * vec[n - 1] << "\n";
	}
	// for (auto x : cnt) {
	// 	cerr << x << " ";
	// }
	// cerr << "\n";
	// for (auto x : sum) {
	// 	cerr << x << " ";
	// }
	// cerr << "\n";

	return 0;
}
