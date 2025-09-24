/*
首先要注意的是，每一个子串 "11 "都会将问题分割成两个子问题，因为位于相对两侧的兔子不能相互影响。例如，在字符串 $0110$ 中，分别位于 $1$ 和 $4$ 位置的兔子不能相互影响。

第二个观察结果是，如果我们对字符串进行拆分，使得每个子问题都不包含两个连续的 $1$ ，那么字符串 $101010 \dots 0101$ （没有连续的 0）是可解的，如果 0 的个数是偶数，因为我们可以按以下方式匹配兔子 $1R1L1R \dots R1L1$ （其中 $R$ 表示我们放置一只向右看的兔子， $L$ 表示我们放置一只向左看的兔子）。

最后一个观察结果是，如果我们有两个连续的 $0$ ，我们就可以用它们来拆分问题，使每个子问题看起来都像这个带有奇数个 $0$ 的交替模式（ $101010 \dots 0101$ ）。因此，我们唯一需要寻找的就是带有奇数个 0 的交替模式子串。

我们还应该注意边界条件。如果字符串以 0 开始或结束，我们可以忽略该位置，将兔子放在边界上；这些情况在示例测试中都存在。

或者，我们也可以使用 dp 来解决问题，即考虑 $dp_{i, L}$ = 是否可以解决前缀 ${0, 1, \dots, i}$ 的问题，将兔子放置在向左看的位置 $i$ ，并以同样的方式定义 $dp_{i, R}$ 。


*/
#include <bits/stdc++.h>
using namespace std;

void solve()
{
	int n;
	cin >> n;
	string s;
	cin >> s;
	bool ok = true;
	bool curr = (s[0] == '1');
	int cnt = 0;
	for (int i = 0; i < n; i++)
	{
		if (s[i] == '0')
			cnt++;
		if (i == 0)
			continue;
		if (s[i] == s[i - 1] && s[i] == '0')
			curr = false;
		if (s[i] == s[i - 1] && s[i] == '1')
		{
			if (curr && cnt % 2 == 1)
				ok = false;
			curr = true;
			cnt = 0;
		}
	}

	if (curr && cnt % 2 == 1 && s[n - 1] == '1')
		ok = false;

	cout << (ok ? "YES" : "NO") << "\n";
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while (T--)
		solve();
}