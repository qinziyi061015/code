#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		vector<int> a(2 * n);
		for (int i = 0; i < 2 * n; i++)
			cin >> a[i];
		int m = 2 * n - 1;
		vector<int> addji(n + 2, 0), addou(n + 2, 0);
		vector<int> preji(n + 2, 0), preou(n + 2, 0);
		vector<int> g(m + 1, 0);
		for (int i = 1; i <= m; i++)
			g[i] = a[i] - a[i - 1];
		
		for (int i = 1; i <= m; i++)
		{
			int T = min(i, 2 * n - i);
			if (i & 1)
				addji[T] += g[i];
			else
				addou[T] += g[i];
		}
		for (int k = n; k >= 1; k--)
		{
			preji[k] = preji[k + 1] + addji[k];
			preou[k] = preou[k + 1] + addou[k];
		}
		vector<int> ans(n + 1, 0);
		if (n >= 1)
			ans[1] = preji[1];
		for (int k = 2; k <= n; k++)
		{
			int delta = (k & 1) ? (2 * preji[k]) : (2 * preou[k]);
			ans[k] = ans[k - 1] + delta;
		}
		for (int k = 1; k <= n; k++)
		{
			if (k > 1)
				cout << ' ';
			cout << ans[k];
		}
		cout << '\n';
	}
	return 0;
}
