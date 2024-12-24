#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()

using namespace std;

inline int nxt() {
	int x;
	cin >> x;
	return x;
}

vector<int> read_ints() {
	vector<int> res;
	int x;
	while (cin >> x) {
		res.push_back(x);
	}
	return res;
}

vector<int> read_ints(const string& s) {
	stringstream sstr(s);
	vector<int> res;
	int x;
	while (sstr >> x) {
		res.push_back(x);
	}
	return res;
}

string read_line() {
	string s;
	getline(cin, s);
	return s;
}

vector<string> read_lines() {
	vector<string> res;
	string s;
	while (getline(cin, s)) {
		res.push_back(s);
	}
	return res;
}

struct Node {
	int value;
	string lhs, rhs;
	string op;
};

int main() {
	map<string, Node> M;
	string s;
	while (cin >> s) {
		if (s.back() == ':') {
			s.pop_back();
			int x = nxt();
			assert(x <= 1);
			M[s] = {x, "", "", ""};
			continue;
		}
		string op, t;
		cin >> op >> t;

		string tmp;
		cin >> tmp;
		assert(tmp == "->");
		cin >> tmp;
		M[tmp] = {-1, s, t, op};
	}

	function<int(Node&)> getvalue = [&](Node& nd) {
		if (nd.value == -1) {
			int x = getvalue(M.at(nd.lhs));
			int y = getvalue(M.at(nd.rhs));
			int z = -1;
			if (nd.op == "AND") {
				z = x & y;
			} else if (nd.op == "OR") {
				z = x | y;
			} else if (nd.op == "XOR") {
				z = x ^ y;
			} else {
				cerr << nd.op << "\n";
				assert(false);
			}
			nd.value = z;
		}
		return nd.value;
	};

	long long ans = 0;
	long long mlt = 1;
	for (auto [k, v] : M) {
		if (k[0] == 'z') {
			ans += getvalue(v) * mlt;
			mlt *= 2;
		}
	}
	cout << ans << "\n";

	return 0;
}
