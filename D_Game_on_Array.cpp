// D. Game on Array
// 正确解法（博弈等价转化）：
// 令每个不同的值 v 出现次数为 f。若双方都想最优博弈，最优策略是总选当前“最小的存在值”。
// 这样游戏会分块、顺序地处理每个“不同值”的整条下降链：
//   - 值为 v 的这条链共进行 v 次操作，每次获得的分数都是 f；
//   - 若该链由某人先开始，则他在这条链上获得 ceil(v/2) 次，另一人获得 floor(v/2) 次；
//   - 链处理完后，若 v 为奇数，则轮次翻转；若 v 为偶数，则轮次不变。
// 因此：按 v 升序遍历不同值，将 ceil(v/2)*f / floor(v/2)*f 分别加到当前先手和后手。

#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	if (!(cin >> T)) return 0;
	while (T--) {
		int n; cin >> n;
		vector<long long> a(n);
		for (int i = 0; i < n; ++i) cin >> a[i];
		sort(a.begin(), a.end());

		long long alice = 0, bob = 0;
		bool aliceTurn = true; // 先手 Alice
		for (int i = 0; i < n; ) {
			long long v = a[i];
			long long f = 0;
			while (i < n && a[i] == v) { ++f; ++i; }

			long long firstGets = (v + 1) / 2 * f; // ceil(v/2) * f
			long long secondGets = (v / 2) * f;    // floor(v/2) * f
			if (aliceTurn) {
				alice += firstGets;
				bob   += secondGets;
			} else {
				bob   += firstGets;
				alice += secondGets;
			}
			if (v & 1LL) aliceTurn = !aliceTurn; // v 为奇数则翻转先手
		}

		cout << alice << ' ' << bob << '\n';
	}
	return 0;
}