#include <bits/stdc++.h>
#define fx  __builtin_ctz
using namespace std;

struct Key {
	uint32_t odd; // odd part of original length after removing factors of 2
	int exp;      // value = odd / 2^exp (exp may be negative initially)
};

struct KeyHash {
	size_t operator()(const Key& k) const noexcept {
		return (static_cast<size_t>(k.odd) << 21) ^ static_cast<size_t>(k.exp * 1315423911u);
	}
};
struct KeyEq { bool operator()(const Key& a, const Key& b) const noexcept { return a.odd == b.odd && a.exp == b.exp; } };

static inline long double keyValue(const Key& k) {
	// value = odd * 2^{-exp}
	return ldexpl((long double)k.odd, -k.exp);
}

struct Cmp {
	bool operator()(const Key& a, const Key& b) const {
		// Compare a.value = a.odd / 2^{a.exp} and b.value = b.odd / 2^{b.exp}
		if (a.exp == b.exp) {
			if (a.odd != b.odd) return a.odd < b.odd; // larger odd => larger value
			return false; // equal
		}
		if (a.exp < b.exp) {
			// compare a.odd * 2^{b.exp - a.exp} vs b.odd
			int d = b.exp - a.exp;
			if (d >= 64) return false; // a dominates (shift would overflow b), so a.value > b.value -> return false to keep a on top
			unsigned __int128 left = (unsigned __int128)a.odd << d;
			unsigned __int128 right = (unsigned __int128)b.odd;
			if (left != right) return left < right; // max-heap: return true if a<b
			return false;
		} else {
			// a.exp > b.exp
			int d = a.exp - b.exp;
			if (d >= 64) return true; // b dominates, so a.value < b.value -> return true
			unsigned __int128 left = (unsigned __int128)b.odd << d;
			unsigned __int128 right = (unsigned __int128)a.odd;
			if (left != right) return right < left; // a<b?
			return false;
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T; 
	cin>>T;
	while (T--) {
		int N; long long K; long long X;
		cin >> N >> K >> X;
		vector<uint32_t> A(N);
		for (int i = 0; i < N; ++i) cin >> A[i];

		// Count initial levels by canonical key: (odd, exp=-ctz(A)) so that value = odd / 2^{exp} = A
		unordered_map<Key, long long, KeyHash, KeyEq> cnt;
		cnt.reserve(N * 2);
		auto push_add = [&](const Key& k, long long add) {
			auto it = cnt.find(k);
			if (it == cnt.end()) cnt.emplace(k, add);
			else it->second += add;
		};

		for (uint32_t a : A) {
			int z = (a == 0 ? 0 :fx(a));
			Key k{a >> z, -z};
			push_add(k, 1);
		}

		// Build max-heap of keys
		priority_queue<Key, vector<Key>, Cmp> pq;
		pq = {};
		for (auto& kv : cnt) pq.push(kv.first);

		auto get_count = [&](const Key& k) -> long long {
			auto it = cnt.find(k);
			return (it == cnt.end() ? 0LL : it->second);
		};

		auto inc_count = [&](const Key& k, long long add) {
			auto it = cnt.find(k);
			if (it == cnt.end()) {
				cnt.emplace(k, add);
				pq.push(k);
			} else {
				it->second += add;
			}
		};

		// Consume K splits in batches at the current maximum level
		while (K > 0 && !pq.empty()) {
			Key top = pq.top(); pq.pop();
			long long c = get_count(top);
			if (c == 0) continue; // stale

			if (K >= c) {
				// Split all c sticks at this level
				K -= c;
				cnt.erase(top);
				Key child{top.odd, top.exp + 1};
				inc_count(child, 2 * c);
			} else {
				// Split only K sticks here, leave c-K at this level
				long long s = K; // number of splits
				cnt[top] = c - s;
				Key child{top.odd, top.exp + 1};
				inc_count(child, 2 * s);
				K = 0;
				// K exhausted
				// reinsert remaining top level for final selection
				pq.push(top);
				break;
			}
		}

		// Now K == 0, select X-th largest by consuming counts in order
		long double answer = 0.0L;
		while (!pq.empty()) {
			Key top = pq.top(); pq.pop();
			long long c = get_count(top);
			if (c == 0) continue;
			if (X <= c) { answer = keyValue(top); break; }
			X -= c;
		}

		cout.setf(std::ios::fixed); cout << setprecision(12) << (double)answer << '\n';
	}

	return 0;
}