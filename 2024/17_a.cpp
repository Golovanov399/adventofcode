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

using u64 = uint64_t;

int main() {
	u64 reg[3];
	{
		for (int i = 0; i < 3; ++i) {
			string s;
			cin >> s;
			cin >> s;
			cin >> reg[i];
		}
		string s;
		cin >> s;
	}
	vector<int> program;
	{
		string s;
		cin >> s;
		for (int i = 0; i < (int)s.size(); i += 2) {
			program.push_back(s[i] - '0');
		}
	}

	auto combo_value = [&](int operand) -> u64 {
		assert(operand != 7);
		if (operand <= 3) {
			return operand;
		} else {
			return reg[operand - 4];
		}
	};

	int pc = 0;
	vector<int> output;
	while (pc < (int)program.size()) {
		int opcode = program[pc];
		int operand = program[pc + 1];
		pc += 2;

		if (opcode == 0) {
			reg[0] >>= combo_value(operand);
		} else if (opcode == 1) {
			reg[1] ^= operand;
		} else if (opcode == 2) {
			reg[1] = combo_value(operand) & 7;
		} else if (opcode == 3) {
			if (reg[0]) {
				pc = operand;
			}
		} else if (opcode == 4) {
			reg[1] ^= reg[2];
		} else if (opcode == 5) {
			output.push_back(combo_value(operand) & 7);
		} else if (opcode == 6) {
			reg[1] = reg[0] >> combo_value(operand);
		} else if (opcode == 7) {
			reg[2] = reg[0] >> combo_value(operand);
		} else {
			assert(false);
		}
	}

	for (int i = 0; i < (int)output.size(); ++i) {
		if (i) {
			cout << ",";
		}
		cout << output[i];
	}
	cout << "\n";

	return 0;
}
