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

struct Node {
	bool is_list;
	int val;
	vector<Node*> items;
};

Node* parse(const string& s, int& i) {
	if (isdigit(s[i])) {
		int x = 0;
		while (i < (int)s.length() && isdigit(s[i])) {
			x = x * 10 + s[i] - '0';
			++i;
		}
		return new Node{false, x, {}};
	}
	auto res = new Node{true, 0, {}};
	++i;
	while (s[i] != ']') {
		if (s[i] == ',') {
			++i;
		}
		res->items.push_back(parse(s, i));
	}
	++i;
	return res;
}

int sign(int x) {
	return x < 0 ? -1 : x > 0;
}

int cmp(Node* a, Node* b) {
	if (!a->is_list && !b->is_list) {
		// cerr << "comparing " << a->val << " and " << b->val << ": " << sign(a->val - b->val) << "\n";
		return sign(a->val - b->val);
	}
	vector<Node*> left = a->is_list ? a->items : vector{a};
	vector<Node*> right = b->is_list ? b->items : vector{b};
	for (int i = 0; i < (int)left.size() || i < (int)right.size(); ++i) {
		if (i >= (int)left.size()) {
			return -1;
		}
		if (i >= (int)right.size()) {
			return 1;
		}
		if (int s = cmp(left[i], right[i]); s) {
			return s;
		}
	}
	return 0;
}

void output(Node* node) {
	if (node->is_list) {
		cerr << "[";
		bool fp = true;
		for (auto x : node->items) {
			if (!fp) {
				cerr << ",";
			}
			fp = false;
			output(x);
		}
		cerr << "]";
	} else {
		cerr << node->val;
	}
}

int main() {
	string s, t;
	int idx = 0;
	int sum = 0;
	while (cin >> s >> t) {
		++idx;
		int i = 0, j = 0;
		auto sn = parse(s, i);
		auto tn = parse(t, j);
		// output(sn);
		// cerr << ", ";
		// output(tn);
		// cerr << "\n";
		if (cmp(sn, tn) < 0) {
			// cerr << idx << " ";
			sum += idx;
		}
	}
	cout << sum << "\n";

	return 0;
}
