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

struct Op {
	string type;
	vector<string> args;
};

struct State {
	vector<int> input;
	map<string, long long> mem;

	long long get(string x) const {
		if (mem.contains(x)) {
			return mem.at(x);
		} else {
			return stoi(x);
		}
	}

	void step(const Op& op) {
		if (op.type == "inp") {
			mem[op.args[0]] = input.back();
			input.pop_back();
		} else if (op.type == "add") {
			long long x = get(op.args[1]);
			mem[op.args[0]] += x;
		} else if (op.type == "mul") {
			long long x = get(op.args[1]);
			mem[op.args[0]] *= x;
		} else if (op.type == "div") {
			long long x = get(op.args[1]);
			mem[op.args[0]] /= x;
		} else if (op.type == "mod") {
			long long x = get(op.args[1]);
			mem[op.args[0]] %= x;
		} else if (op.type == "eql") {
			long long x = get(op.args[1]);
			long long& y = mem[op.args[0]];
			y = (y == x);
		} else {
			assert(false);
		}
	}
};

struct Machine {
	vector<Op> code;

	long long run(string inp) {
		State s;
		for (char c : inp) {
			s.input.push_back(c - '0');
		}
		reverse(all(s.input));
		s.mem["w"] = 0;
		s.mem["x"] = 0;
		s.mem["y"] = 0;
		s.mem["z"] = 0;

		for (const auto& op : code) {
			s.step(op);
		}

		return s.get("z");
	}
};

void read_and_run(string input) {
	Machine m;
	string s;
	while (getline(cin, s)) {
		Op op;
		op.type = s.substr(0, s.find(' '));
		s = s.substr(s.find(' ') + 1);
		s += ' ';
		while (!s.empty()) {
			op.args.push_back(s.substr(0, s.find(' ')));
			s = s.substr(s.find(' ') + 1);
		}
		m.code.push_back(op);
	}
	cerr << m.run(input) << "\n";
}

int main() {
	vector<int> xadds;
	vector<char> is_zero(14);
	vector<char> is_div(14);
	vector<pair<int, int>> st;
	vector<pair<int, int>> which(14, {-1, 0});
	for (int i = 0; i < 14; ++i) {
		string s;
		getline(cin, s);	// inp w
		getline(cin, s);	// mul x 0
		getline(cin, s);	// add x z
		getline(cin, s);	// mod x 26
		if (!st.empty()) {
			which[i] = st.back();
		}
		getline(cin, s);	// div z ?
		if (s == "div z 26") {
			is_div[i] = 1;
			st.pop_back();
		} else {
			assert(s == "div z 1");
		}
		getline(cin, s);	// add x ?
		s = s.substr(s.find(' ') + 1);
		s = s.substr(s.find(' ') + 1);
		int x_add = stoi(s);
		if (x_add >= 10 || x_add <= -25) {
			st.push_back({i, x_add});
		} else {
			is_zero[i] = 1;
		}
		xadds.push_back(x_add);
		for (int j = 0; j < 10; ++j) {
			getline(cin, s);
		}
		s = s.substr(s.find(' ') + 1);
		s = s.substr(s.find(' ') + 1);
		if (!is_zero[i]) {
			st.back().second = stoi(s);
		}
		for (int j = 0; j < 2; ++j) {
			getline(cin, s);
		}
	}
	string res(14, '9');
	for (int i = 0; i < 14; ++i) {
		if (is_zero[i]) {
			cerr << "#" << which[i].first << " + " << which[i].second + xadds[i] << " = #" << i << "\n";
			if (which[i].second + xadds[i] > 0) {
				res[which[i].first] = '9' - (which[i].second + xadds[i]);
			} else {
				res[i] = '9' + (which[i].second + xadds[i]);
			}
		}
	}
	cout << res << "\n";

	return 0;
}
