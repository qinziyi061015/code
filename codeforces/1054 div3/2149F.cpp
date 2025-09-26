#include <bits/stdc++.h>
#define int unsigned long long
using namespace std;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--)
	{
		int h, d;
		cin >> h >> d;
		if (h == 1)
		{
			cout << 2 * d << "\n";
			continue;
		}
		// m段连续跑的块，有m-1段空隙，最优情况是，这m段连续跑长度均匀，如果不完全均匀，余数平摊，空隙休息一次
		// h个1，恢复m-1格血
		int l = 1, r = d, ans = -1;
		while (l <= r)
		{
			int mid = (l + r) / 2;
			int q = d / mid;
			int r = d - q * mid;
			if (r * (q / 2 + 1) * (q + 1) + (mid - r) * q * (q + 1) / 2 - (mid - 2) <= h)
			{
				ans = mid;
				r = mid - 1;
				break;
			}
			else
				l = mid + 1;
		}
		if (ans != -1)
			cout << d + ans - 1 << "\n";
		else
			cout << d * 2 + 1 - h << "\n";
	}
	return 0;
}