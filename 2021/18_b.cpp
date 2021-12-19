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

struct Node {
	Node *l, *r;
	Node *p;
	int x;

	Node(): l(nullptr), r(nullptr), p(nullptr), x(-1) {}
};

int pos = 0;
Node* parse(const string& s) {
	if (s[pos] == '[') {
		Node* res = new Node();
		++pos;
		res->l = parse(s);
		assert(s[pos++] == ',');
		res->r = parse(s);
		assert(s[pos++] == ']');
		res->l->p = res;
		res->r->p = res;
		return res;
	} else {
		assert(isdigit(s[pos]));
		Node* res = new Node();
		res->x = s[pos] - '0';
		++pos;
		return res;
	}
}

void show(Node* node) {
	if (node->x > -1) {
		cerr << node->x;
	} else {
		cerr << "[";
		show(node->l);
		cerr << ",";
		show(node->r);
		cerr << "]";
	}
}

void reduce(Node*);

Node* add(Node* a, Node* b) {
	Node* res = new Node();
	res->l = a;
	res->r = b;
	a->p = b->p = res;
	reduce(res);
	return res;
}

void add_left(Node* node, int x) {
	bool ok = false;
	while (node->p) {
		auto p = node->p;
		if (p->r == node) {
			node = p->l;
			ok = true;
			break;
		} else {
			node = p;
		}
	}
	if (!ok) {
		return;
	}
	while (node->r) {
		node = node->r;
	}
	node->x += x;
}

void add_right(Node* node, int x) {
	bool ok = false;
	while (node->p) {
		auto p = node->p;
		if (p->l == node) {
			node = p->r;
			ok = true;
			break;
		} else {
			node = p;
		}
	}
	if (!ok) {
		return;
	}
	while (node->l) {
		node = node->l;
	}
	node->x += x;
}

bool try_explode(Node* node, int d = 0) {
	if (!node) {
		return false;
	}
	if (d == 4 && node->l) {
		int le = node->l->x;
		int ri = node->r->x;
		node->l = node->r = nullptr;
		node->x = 0;
		add_left(node, le);
		add_right(node, ri);
		return true;
	}
	if (!try_explode(node->l, d + 1)) {
		return try_explode(node->r, d + 1);
	} else {
		return true;
	}
}

bool try_split(Node* node) {
	if (!node) {
		return false;
	}
	if (node->x >= 10) {
		auto le = new Node();
		le->x = node->x / 2;
		auto ri = new Node();
		ri->x = (node->x + 1) / 2;
		node->x = -1;
		le->p = ri->p = node;
		node->l = le;
		node->r = ri;
		return true;
	} else if (node->x > -1) {
		return false;
	}
	if (!try_split(node->l)) {
		return try_split(node->r);
	} else {
		return true;
	}
}

void reduce(Node* root) {
	while (true) {
		// show(root);
		// cerr << "\n";
		if (try_explode(root)) {
			continue;
		}
		if (try_split(root)) {
			continue;
		}
		break;
	}
}

long long mag(Node* node) {
	if (node->x > -1) {
		return node->x;
	} else {
		return mag(node->l) * 3 + mag(node->r) * 2;
	}
}

int main() {
	vector<string> strs;
	string s;
	while (cin >> s) {
		strs.push_back(s);
	}

	long long ans = 0;
	for (int i = 0; i < (int)strs.size(); ++i) {
		for (int j = 0; j < (int)strs.size(); ++j) {
			if (i == j) {
				continue;
			}
			pos = 0;
			Node *a = parse(strs[i]);
			pos = 0;
			Node *b = parse(strs[j]);
			Node *node = add(a, b);
			ans = max(ans, mag(node));
		}
	}
	cerr << ans << "\n";

	return 0;
}
