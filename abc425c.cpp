
#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int N, Q;
	if (!(cin >> N >> Q))
		return 0;
	vector<int64> a(N);
	for (int i = 0; i < N; i++)
		cin >> a[i];
	vector<int64> pre(N + 1, 0);
	for (int i = 0; i < N; i++)
		pre[i + 1] = pre[i] + a[i];
	auto sum = [&](int l, int r) -> int64 { 
		if (l <= r)
			return pre[r + 1] - pre[l];
		return (pre[N] - pre[l]) + (pre[r + 1] - pre[0]);
	};
	int shift = 0; 
	while (Q--)
	{
		int type;
		cin >> type;
		if (type == 1)
		{
			int c;
			cin >> c;
			shift = (shift + c) % N;
		}
		else
		{
			int l, r;
			cin >> l >> r; 
			int L = (shift + (l - 1)) % N;
			int R = (shift + (r - 1)) % N;
			long long ans = sum(L, R);
			cout << ans << "\n";
		}
	}
	return 0;
}