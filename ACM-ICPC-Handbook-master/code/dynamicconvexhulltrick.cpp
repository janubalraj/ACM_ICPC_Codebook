const long long is_query = -(1ll<<62);
struct Line {
	long long m, b;
	mutable function<const Line*()> succ;
	bool operator<(const Line& rhs) const {
		if (rhs.b != is_query)  return m < rhs.m;
		const Line* s = succ();
		if (!s) return 0;
		long long x = rhs.m;
		return ((long double)b - s->b)/x < (s->m - m);
	}
};
struct HullDynamic : public multiset<Line> {
	// will maintain upper hull for maximum
	bool bad(iterator y) {
		auto z = next(y);
		if (y == begin()) {
			if (z == end()) return 0;
			return y->m == z->m && y->b <= z->b;
		}
		auto x = prev(y);
		if (z == end()) return y->m == x->m && y->b <= x->b;
		return ((long double)(x->b - y->b))/(y->m - x->m) >= ((long double)(y->b - z->b))/(z->m - y->m);
	}
	void insert_line(long long m, long long b) {
		auto y = insert({ m, b });
		y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
		if (bad(y)) { erase(y); return; }
		while (next(y) != end() && bad(next(y))) erase(next(y));
		while (y != begin() && bad(prev(y))) erase(prev(y));
	}
	long long eval(long long x) {
		auto l = *lower_bound((Line) { x, is_query });
		return l.m * x + l.b;
	}
};
