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

const int cost[4] = {1, 10, 100, 1000};
const int valid_mask = 0b111111111111111111010101011;
const int N = 27;

int d[N][N];
int need_mask[N][N];

void print_char(int i) {
	if (i == -1) {
		cerr << ".";
	} else {
		cerr << "\033[1;" << (31 + i) << "m" << (char)('A' + i) << "\033[0m";
	}
}

struct State {
	int who[N];
	int mask;
	int last;

	bool operator <(const State& ot) const {
		if (last != ot.last) {
			return last < ot.last;
		} else {
			return memcmp(who, ot.who, sizeof(who)) < 0;
		}
	}

	bool is_final() const {
		for (int i = 11; i < N; ++i) {
			if (who[i] != (i - 11) % 4) {
				return false;
			}
		}
		return true;
	}

	bool can(int from, int to) const {
		if (who[from] == -1) {
			return false;
		}
		if (who[from] == last) {
			return false;
		}
		if (!(valid_mask & (1 << to))) {
			return false;
		}
		if (mask & need_mask[from][to]) {
			return false;
		}
		if (from < 11 && to < 11) {
			return false;
		}
		// if (to == 1 && !~who[0]) {
		// 	return false;
		// }
		// if (to == 9 && !~who[10]) {
		// 	return false;
		// }
		if (to >= 11) {
			if (who[from] != (to - 11) % 4) {
				return false;
			}
			for (int i = to + 4; i < N; i += 4) {
				if (who[i] != who[from]) {
					return false;
				}
			}
		}
		return true;
	}

	void show() {
		cerr << "\n";
		cerr << string(13, '#') << "\n";
		cerr << "#";
		for (int i = 0; i < 11; ++i) {
			// cerr << (who[i] == -1 ? '.' : (char)('A' + who[i]));
			print_char(who[i]);
		}
		cerr << "#\n";
		for (int i = 0; i < (N - 11) / 4; ++i) {
			if (!i) {
				cerr << "##";
			} else {
				cerr << "  ";
			}
			cerr << "#";
			for (int j = 0; j < 4; ++j) {
				print_char(who[11 + 4 * i + j]);
				cerr << "#";
				// cerr << (who[11 + 4 * i + j] == -1 ? '.' : (char)('A' + who[11 + 4 * i + j])) << "#";
			}
			if (!i) {
				cerr << "##";
			}
			cerr << "\n";
		}
		cerr << "  " << string(9, '#') << "\n";
	}
};

int main() {
	for (int i = 0; i < 11; ++i) {
		for (int j = 0; j < 11; ++j) {
			d[i][j] = abs(i - j);
			need_mask[i][j] = (1 << (max(i, j) + 1)) - (1 << min(i, j)) - (1 << i);
		}
	}
	for (int i = 0; i < 11; ++i) {
		for (int j = 11; j < N; ++j) {
			int col = (j - 11) % 4 * 2 + 2;
			int dst = 0;
			int mask = 0;
			for (int k = j; k >= 11; k -= 4) {
				mask |= 1 << k;
				dst += 1;
			}
			mask |= (1 << (max(i, col) + 1)) - (1 << min(i, col));
			dst += abs(i - col);
			need_mask[i][j] = mask ^ (1 << i);
			need_mask[j][i] = mask ^ (1 << j);
			d[i][j] = d[j][i] = dst;
		}
	}
	for (int i = 11; i < N; ++i) {
		for (int j = i + 1; j < N; ++j) {
			int coli = (i - 11) % 4 * 2 + 2;
			int dst = 0;
			int mask = 0;
			for (int k = i; k >= 11; k -= 4) {
				mask |= 1 << k;
				++dst;
			}
			int colj = (j - 11) % 4 * 2 + 2;
			for (int k = j; k >= 11; k -= 4) {
				mask |= 1 << k;
				++dst;
			}
			mask |= (1 << (max(coli, colj) + 1)) - (1 << min(coli, colj));
			dst += abs(coli - colj);
			need_mask[i][j] = mask ^ (1 << i);
			need_mask[j][i] = mask ^ (1 << j);
			d[i][j] = dst;
			d[j][i] = dst;
		}
	}

	State initial;
	memset(initial.who, -1, sizeof(initial.who));
	initial.last = -1;
	initial.mask = (1 << N) - (1 << 11);
	{
		string s;
		cin >> s;
		cin >> s;
		for (int i = 0; i < (N - 11) / 4; ++i) {
			if (i == 1) {
				s = "#D#C#B#A#";
			} else if (i == 2) {
				s = "#D#B#A#C#";
			} else {
				cin >> s;
			}
			for (int j = 0; j < 4; ++j) {
				initial.who[11 + 4 * i + j] = s[3 - 2 * (i > 0) + 2 * j] - 'A';
			}
		}
	}

	map<State, int> dist;
	map<State, State> prv;
	set<pair<int, State>> S;
	dist[initial] = 0;
	S.insert({0, initial});
	int last_printed = -1;
	while (!S.empty()) {
		auto [dst, s] = *S.begin();
		S.erase(S.begin());
		if (dst % 100 == 0 && dst > last_printed) {
			cerr << dst << " ";
			last_printed = dst;
		}
		if (s.is_final()) {
			while (prv.contains(s)) {
				s.show();
				s = prv[s];
			}
			s.show();
			cout << dst << "\n";
			return 0;
		}
		// if (dst > 1000) {
		// 	s.show();
		// 	return 0;
		// }
		for (int i = 0; i < N; ++i) {
			if (s.who[i] == -1) {
				continue;
			}
			for (int j = 0; j < N; ++j) {
				if (i == j) {
					continue;
				}
				if (s.can(i, j)) {
					auto t = s;
					assert(s.who[i] > -1);
					int nd = dst + cost[s.who[i]] * d[i][j];
					// cerr << i << " " << j << ": " << d[i][j] << "\n";
					assert(d[i][j] > 0);
					t.last = t.who[i];
					if (j >= 11) {
						t.last = -1;
					}
					swap(t.who[i], t.who[j]);
					t.mask ^= (1 << i) ^ (1 << j);

					if (auto it = dist.find(t); it != dist.end()) {
						if (nd < it->second) {
							S.erase({it->second, t});
							it->second = nd;
							prv[t] = s;
							S.insert({it->second, t});
						}
					} else {
						dist[t] = nd;
						prv[t] = s;
						S.insert({nd, t});
					}
				}
			}
		}
	}

	return 0;
}
