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

using Piece = vector<string>;
const vector<string> pieces[5] = {
	{"####"},
	{".#.", "###", ".#."},
	{"###", "..#", "..#"},
	{"#", "#", "#", "#"},
	{"##", "##"}
};

const int w = 7;

int main() {
	vector<string> a;
	string pattern;
	cin >> pattern;
	int pidx = 0;

	auto getChar = [&]() {
		char res = pattern[pidx++];
		if (pidx == (int)pattern.size()) {
			pidx = 0;
		}
		return res;
	};

	auto intersects = [&](const Piece& piece, int x, int y) {
		if (x < 0 || x + (int)piece[0].size() > w) {
			return true;
		}
		if (y < 0) {
			return true;
		}
		for (int i = 0; i < (int)piece.size(); ++i) {
			if (y + i >= (int)a.size()) {
				continue;
			}
			for (int j = 0; j < (int)piece[i].size(); ++j) {
				if (piece[i][j] == '#' && a[y + i][x + j] == '#') {
					return true;
				}
			}
		}
		return false;
	};

	auto install_piece = [&](const Piece& piece, int x, int y) {
		while (y + (int)piece.size() > (int)a.size()) {
			a.push_back(string(w, '.'));
		}
		for (int i = 0; i < (int)piece.size(); ++i) {
			for (int j = 0; j < (int)piece[i].size(); ++j) {
				if (piece[i][j] == '#') {
					assert(a[y + i][x + j] == '.');
					a[y + i][x + j] = piece[i][j];
				}
			}
		}
	};

	for (int it = 0; it < 2022; ++it) {
		const auto& piece = pieces[it % 5];
		int x = 2;
		int y = (int)a.size() + 3;
		while (true) {
			char c = getChar();
			if (!intersects(piece, x + (c == '>' ? 1 : -1), y)) {
				x += (c == '>' ? 1 : -1);
			}
			if (!intersects(piece, x, y - 1)) {
				y -= 1;
			} else {
				install_piece(piece, x, y);
				break;
			}
		}
		// if (it < 5) {
		// 	for (int i = (int)a.size() - 1; i >= 0; --i) {
		// 		cerr << "|" << a[i] << "|\n";
		// 	}
		// 	cerr << "+" << string(w, '-') << "+\n\n";
		// }
	}
	cout << a.size() << "\n";

	return 0;
}
