#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--)
	{
		int n, k;
		cin >> n >> k;
		vector<int> a(n);
		vector<int> cnt(n + 1);
		for(int i=0;i<n;i++) {
			cin>>a[i];
			cnt[a[i]]++;
		}
		if (k == 0)
		{
			cout << cnt[0] << "\n";
			continue;
		}
		int miss = 0; 
		for (int i = 0; i < k; ++i)
			if (!cnt[i])
				++miss;
		if (cnt[k] == 0)
			cout << miss << "\n";
		else
			cout << max(miss, cnt[k]) << "\n";
	}
	return 0;
}