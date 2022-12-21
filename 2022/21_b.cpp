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

int sign(int x) {
	return x < 0 ? -1 : x > 0;
}

struct Lin {
	long double a, b;

	Lin& operator +=(const Lin& ot) {
		a += ot.a;
		b += ot.b;
		return *this;
	}

	Lin& operator -=(const Lin& ot) {
		a -= ot.a;
		b -= ot.b;
		return *this;
	}

	Lin& operator *=(const Lin& ot) {
		assert(a == 0 || ot.a == 0);
		a = a * ot.b + b * ot.a;
		b *= ot.b;
		return *this;
	}

	Lin& operator /=(const Lin& ot) {
		if (ot.a == 0) {
			a /= ot.b;
			b /= ot.b;
		} else {
			a /= ot.a;
			b /= ot.b;
		}
		return *this;
	}
};

struct Monkey {
	Lin value;
	vector<string> names;
	char op;
	bool calculated;
};

int main() {
	map<string, Monkey> M;
	{
		string s;
		while (getline(cin, s)) {
			auto spl = split(s);
			auto name = spl[0];
			name.pop_back();
			Monkey monke = {Lin{0, 0}, {}, '\0', false};
			if ((int)spl.size() == 2) {
				monke.value = {0, (long double)stoi(spl[1])};
				monke.calculated = true;
			} else {
				monke.names = {spl[1], spl[3]};
				monke.op = spl[2][0];
			}
			M[name] = monke;
		}
	}
	M["root"].op = '-';
	M["humn"].value = {1, 0};

	function<Lin(string)> calc = [&](string name) {
		auto& m = M[name];
		if (m.calculated) {
			return m.value;
		} else {
			auto lhs = calc(m.names[0]);
			auto rhs = calc(m.names[1]);
			m.value = lhs;
			if (m.op == '+') {
				m.value += rhs;
			} else if (m.op == '-') {
				m.value -= rhs;
			} else if (m.op == '*') {
				m.value *= rhs;
			} else if (m.op == '/') {
				m.value /= rhs;
			} else {
				assert(false);
			}
			m.calculated = true;
			return m.value;
		}
	};
	auto val = calc("root");
	cout << setprecision(5) << fixed;
	cout << (long long)round(-val.b / val.a) << "\n";

	return 0;
}
