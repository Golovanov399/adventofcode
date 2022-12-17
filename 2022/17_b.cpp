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

template <uint32_t base>
struct Montgomery {
	using i32 = int32_t;
	using u32 = uint32_t;
	using u64 = uint64_t;

	static constexpr u32 mod() {
		return base;
	}

	static constexpr u32 np = []() {
		u32 x = base;
		for (int i = 0; i < 4; ++i) {
			x *= 2u - base * x;
		}
		return -x;
	}();
	static constexpr u32 r2 = -(u64)(base) % base;

	static_assert(base < (1u << 30));
	static_assert(base * np + 1 == 0);

	static u32 reduce(u64 x) {
		return (x + (u64)((u32)x * np) * base) >> 32;
	}

	u32 x;
	Montgomery(): x(0) {}
	constexpr Montgomery(long long y): x(y ? reduce((u64)(y % base + base) * r2) : 0) {}

	Montgomery& operator +=(const Montgomery& ot) {
		if ((i32)(x += ot.x - 2 * base) < 0) {
			x += 2 * base;
		}
		return *this;
	}

	Montgomery& operator -=(const Montgomery& ot) {
		if ((i32)(x -= ot.x) < 0) {
			x += 2 * base;
		}
		return *this;
	}

	Montgomery& operator *=(const Montgomery& ot) {
		x = reduce((u64)x * ot.x);
		return *this;
	}

	Montgomery& operator /=(const Montgomery& ot) {
		return *this *= ot.inverse();
	}

	friend Montgomery operator +(Montgomery a, const Montgomery& b) {
		a += b;
		return a;
	}

	friend Montgomery operator -(Montgomery a, const Montgomery& b) {
		a -= b;
		return a;
	}

	friend Montgomery operator *(Montgomery a, const Montgomery& b) {
		a *= b;
		return a;
	}

	friend Montgomery operator /(Montgomery a, const Montgomery& b) {
		a /= b;
		return a;
	}

	Montgomery operator -() const {
		return Montgomery() - *this;
	}

	u32 get() const {
		u32 res = reduce(x);
		return res < base ? res : res - base;
	}

	u32 operator ()() const {
		return get();
	}

	Montgomery inverse() const {
		return pow(base - 2);
	}

	Montgomery inv() const {
		return inverse();
	}

	Montgomery pow(int64_t p) const {
		if (p < 0) {
			return pow(-p).inverse();
		}
		Montgomery res = 1;
		Montgomery a = *this;
		while (p) {
			if (p & 1) {
				res *= a;
			}
			p >>= 1;
			a *= a;
		}
		return res;
	}

	friend istream& operator >>(istream& istr, Montgomery& m) {
		long long x;
		istr >> x;
		m = Montgomery(x);
		return istr;
	}

	friend ostream& operator <<(ostream& ostr, const Montgomery& m) {
		return ostr << m.get();
	}

	bool operator ==(const Montgomery& ot) const {
		return (x >= base ? x - base : x) == (ot.x >= base ? ot.x - base : ot.x);
	}

	bool operator !=(const Montgomery& ot) const {
		return (x >= base ? x - base : x) != (ot.x >= base ? ot.x - base : ot.x);
	}

	explicit operator int64_t() const {
		return x;
	}

	explicit operator bool() const {
		return x;
	}
};

constexpr int mod1 = 998'244'353;
constexpr int mod2 = 987'898'789;
using Mint1 = Montgomery<mod1>;
using Mint2 = Montgomery<mod2>;

template <typename T>
vector<T> find_linear_recurrence(const vector<T>& a) {
	vector<T> p;
	auto get = [&](int idx) -> T {
		T res = 0;
		for (int i = 0; i < (int)p.size(); ++i) {
			res += a[idx - 1 - i] * p[i];
		}
		return res;
	};
	vector<T> last_incorrect;
	int last_idx = -1;
	for (int i = 0; i < (int)a.size(); ++i) {
		auto cur = get(i);
		if (cur == a[i]) {
			continue;
		}
		auto new_p = p;
		bool need_to_upd = true;
		if (new_p.empty()) {
			new_p.assign(i + 1, 0);
		} else {
			const int sz = (i - last_idx - 1) + (int)last_incorrect.size();
			if (sz > (int)new_p.size()) {
				new_p.resize(sz);
			} else {
				need_to_upd = false;
			}
			for (int j = 0; j < (int)last_incorrect.size(); ++j) {
				new_p[i - last_idx - 1 + j] += last_incorrect[j] * (a[i] - cur);
			}
		}
		if (need_to_upd) {
			last_incorrect = p;
			last_incorrect.insert(last_incorrect.begin(), -1);
			auto inv = 1 / (cur - a[i]);
			for (auto& x : last_incorrect) {
				x *= inv;
			}
			last_idx = i;
		}
		p.swap(new_p);
	}
	return p;
}

template <typename T>
T get_nth_term_of_recurrence(const vector<T>& rec, const vector<T>& initial, long long n) {
	if (n < (int)initial.size()) {
		return initial[n];
	}
	const int sz = (int)rec.size();
	auto mult = [&](const vector<T>& a, const vector<T>& b) {
		vector<T> res(sz * 2);
		for (int i = 0; i < sz; ++i) {
			for (int j = 0; j < sz; ++j) {
				res[i + j] += a[i] * b[j];
			}
		}
		for (int i = 2 * sz - 1; i >= sz; --i) {
			if (!res[i]) {
				continue;
			}
			for (int j = 0; j < sz; ++j) {
				res[i - 1 - j] += res[i] * rec[j];
			}
		}
		res.resize(sz);
		return res;
	};

	if (sz == 1) {
		T answer = initial[0];
		T cur = rec[0];
		while (n) {
			if (n & 1ll) {
				answer *= cur;
			}
			n >>= 1;
			cur *= cur;
		}
		return answer;
	}

	vector<T> res(sz);
	res[0] = 1;
	vector<T> a(sz);
	a[1] = 1;
	while (n) {
		if (n & 1ll) {
			res = mult(res, a);
		}
		n >>= 1;
		a = mult(a, a);
	}
	T answer = 0;
	for (int i = 0; i < sz; ++i) {
		answer += res[i] * initial[i];
	}
	return answer;
}

template <typename T>
T guess_nth_term(const vector<T>& a, long long n) {
	auto rec = find_linear_recurrence(a);
	return get_nth_term_of_recurrence(rec, a, n);
}

long long inv(long long a, long long b) {
	return a == 1 ? 1 : b - __int128_t(inv(b % a, a)) * b / a % b;
}

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

	auto show = [&]() {
		for (int i = (int)a.size() - 1; i >= 0; --i) {
			cerr << "|" << a[i] << "|\n";
		}
		cerr << "+" << string(w, '-') << "+\n\n";
	};

	const long long its = 1000000000000;

	vector<Mint1> answers1;
	vector<Mint2> answers2;

	for (int it = 0; it < 30000; ++it) {
		answers1.push_back(a.size());
		answers2.push_back(a.size());
		// {
		// 	int cnt = 0;
		// 	int le = -1, ri = -1;
		// 	for (int i = 0; i < w; ++i) {
		// 		int j = (int)a.size() - 1;
		// 		while (j >= 0 && a[j][i] == '.') {
		// 			--j;
		// 		}
		// 		if (j == (int)a.size() - 1 && j > -1) {
		// 			++cnt;
		// 			if (le == -1) {
		// 				le = i;
		// 			}
		// 			ri = i;
		// 		}
		// 	}
		// 	if (cnt > 1 && cnt != ri - le + 1) {
		// 		show();
		// 		return 0;
		// 	}
		// }
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
		// if (it < 25 && it % 5 == 4) {
		// 	show();
		// }
	}
	cerr << "Done\n";
	auto rec1 = find_linear_recurrence(answers1);
	auto rec2 = find_linear_recurrence(answers2);
	assert(rec1.size() == rec2.size());
	const int period = rec1.size();
	cerr << period << "\n";

	auto true_ans = [&](long long n) {
		long long ans1 = get_nth_term_of_recurrence(rec1, answers1, n)();
		long long ans2 = get_nth_term_of_recurrence(rec2, answers2, n)();
		return ans1 + mod1 * ((ans2 - ans1 + mod2) * inv(mod1, mod2) % mod2);
	};
	cerr << true_ans(2022) << "\n";
	cerr << true_ans(its) << "\n";

	// vector<long long> lans(answers.size());
	// vector<long long> lrec(rec.size());
	// for (int i = 0; i < (int)answers.size(); ++i) {
	// 	lans[i] = answers[i]();
	// }
	// for (int i = 0; i < (int)rec.size(); ++i) {
	// 	int x = rec[i]();
	// 	if (x > mod / 2) {
	// 		x = mod - x;
	// 	}
	// 	lrec[i] = x;
	// }
	// cout << get_nth_term_of_recurrence(lrec, lans, its) << "\n";
	// cout << get_nth_term_of_recurrence(rec, answers, 2022) << "\n";

	// {
	// 	int last = (int)answers.size();
	// 	last -= last % period;
	// 	last = last - period + its % period;
	// 	cout << answers[last] + (answers[last] - answers[last - period]) * ((its - last) / period) << "\n";
	// }

	return 0;
}
