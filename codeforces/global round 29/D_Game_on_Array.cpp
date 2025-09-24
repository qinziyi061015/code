/*
选奇数 x 则不同：比如你选 x=1，对手没法选 0（不存在），所以这种“跟随”被打断了。也就是说，真正决定胜负的是奇数这边的“堆”。
因此，游戏的本质可以“压缩”为：我们有若干“堆”，每个堆的大小是某个奇数值的出现次数。把这些堆大小降序排列为 f0 ≥ f1 ≥ … ≥ fk。题解声称，最优对局下先手的净胜分就是： S = f0 − f1 + f2 − f3 + … = Σ (-1)^i f_i

为什么是交替和 S？
题解给了策略与三种情况的分析，核心在于“偶数选择都能被‘复制策略’（选 x−1）中和”，而奇数堆之间的对抗，等价于两人轮流从降序堆列中拿分：先手拿 f0，后手拿 f1，先手拿 f2，… 这正是交替和。

更细一点的策略说明（对应题解三点）：

如果对手直接选了某个奇数堆 f_i，且 i 为奇数（也就是原本轮到后手拿的位置），那么按归纳你最终能拿到恰好 S 的分差。
如果对手选了某个奇数堆 f_i，且 i 为偶数（他“抢走了你该拿的堆”），你就立刻拿 f_{i−1}，两步合计得到 f_{i−1} − f_i ≥ 0，相当于回到了“不会比 S 更差”的局面（归纳可得最终 ≥ S）。
如果对手选了偶数 x，你就复制选择 x−1，并如此反复，直到他最终不得不选择一个奇数。期间你可能会多拿走若干个奇数堆，题解用“符号翻转”的方式严格证明这不会让你的最终分差低于 S（翻转后多出来的那一段交替和 ≥ 0）。
同理，用完全对称的策略，后手也能保证至少 −S。所以上下界相遇，游戏值就是 S。

实现步骤（你代码应当就是这么做的）
统计每个数的出现次数 cnt[val]。
把所有“奇数值”的出现次数提取出来，形成数组 F。
将 F 降序排序。
计算交替和 S = F[0] − F[1] + F[2] − F[3] + …。
这就是先手的净胜分；如果题目只问谁赢：
S > 0，先手赢；
S = 0，平局（或按题意约定）；
S < 0，后手赢（净胜 |S|）。
小例子帮助直觉
若奇数的频次是 [5, 3, 1]，则 S = 5 − 3 + 1 = 3。意味着先手能净胜 3 分。
若奇数的频次是 [2, 2]，则 S = 2 − 2 = 0。意味着最优对局平分秋色（净胜 0）。
为什么不需要管偶数的频次？
因为只要你（或对手）拿了一个偶数 x，另一个人立刻就能用 x−1（奇数）“跟随”，把你这一步的优势抵消甚至反超；所以“主动权”不在偶数上，胜负被奇数堆主导。
如果你希望，我也能在你的 D_Game_on_Array.cpp 里加一段中文注释，简要写上上述要点，方便以后回顾
*/
#include <bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
using ld = long double;
using ll = long long;
const int maxN = 2e5 + 5;
const int INF = 1e18;
const int MOD = 1e9 + 7;
#define F first
#define S second

int power(int a, int b)
{
	if (b == 0)
		return 1;
	if (b % 2)
		return a * power(a, b - 1) % MOD;
	return power(a * a % MOD, b / 2);
}
int inv(int a)
{
	return power(a, MOD - 2);
}
vector<int> fact(maxN);
vector<int> invfact(maxN);

signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;

		map<int, int> freq;
		int s = 0;
		int sum = 0;
		for (int i = 0; i < n; i++)
		{
			int x;
			cin >> x;
			if (x % 2)
				freq[x]++, s += x - 1;
			else
				s += x;
			sum += x;
		}
		int A = s / 2;
		;
		vector<int> b;
		for (auto [u, v] : freq)
			b.push_back(v);
		sort(b.rbegin(), b.rend());
		for (int i = 0; i < b.size(); i += 2)
			A += b[i];
		cout << A << " " << sum - A << endl;
	}
}