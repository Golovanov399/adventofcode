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
		if (s > t) {
			swap(s, t);
		}
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

	vector<string> ans;
	auto upd = [&](string s, string t) {
		swap(M.at(s), M.at(t));
		ans.push_back(s);
		ans.push_back(t);
	};

	auto find_by_ops = [&](string s, string t, string op) -> string {
		if (s > t) {
			swap(s, t);
		}
		for (const auto& [k, v] : M) {
			if (v.op == op && v.lhs == s && v.rhs == t) {
				return k;
			}
		}
		return "";
	};
	const int n = [&]() {
		int n = 0;
		while (true) {
			string s = "x";
			s += (char)('0' + n / 10);
			s += (char)('0' + n % 10);
			if (M.contains(s)) {
				++n;
			} else {
				break;
			}
		}
		return n;
	}();

	vector<string> all_keys;
	for (const auto& p : M) {
		all_keys.push_back(p.first);
	}

	string carry = "";
	upd("jgt", "mht");
	for (int i = 0; i < n; ++i) {
		string x = "x", y = "y";
		x += (char)('0' + i / 10);
		x += (char)('0' + i % 10);
		y += (char)('0' + i / 10);
		y += (char)('0' + i % 10);

		auto old = carry;
		auto xxy = find_by_ops(x, y, "XOR");
		auto xay = find_by_ops(x, y, "AND");
		string cx = !i ? "" : find_by_ops(carry, xxy, "XOR");
		string ca = !i ? "" : find_by_ops(carry, xxy, "AND");
		carry = !i ? xay : find_by_ops(ca, xay, "OR");

		auto repeat = [&]() {
			carry = old;
			xxy = find_by_ops(x, y, "XOR");
			xay = find_by_ops(x, y, "AND");
			cx = find_by_ops(carry, xxy, "XOR");
			ca = find_by_ops(carry, xxy, "AND");
			carry = find_by_ops(ca, xay, "OR");
		};

		cerr << i << ": " << xxy << " " << xay << " " << cx << " " << ca << " " << carry << "\n";
		if (i == 0) {
			if (xxy != "z00") {
				upd(xxy, "z00");
				repeat();
			}
		} else {
			string z = "z";
			z += x.substr(1);

			if (cx != z) {
				upd(cx, z);
				repeat();
			}
		}
		cerr << i << ": " << xxy << " " << xay << " " << cx << " " << ca << " " << carry << "\n";
		if (i > 0 && (cx == "" || ca == "" || carry == "")) {
			cerr << i << " !!\n";
			return 0;
		}
	}

	sort(all(ans));
	for (int i = 0; i < (int)ans.size(); ++i) {
		if (i) {
			cout << ",";
		}
		cout << ans[i];
	}
	cout << "\n";

	return 0;
}
