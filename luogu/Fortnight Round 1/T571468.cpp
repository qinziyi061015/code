#include <bits/stdc++.h>
using namespace std;
static const int MOD = 1'000'000'007;
long long modpow(long long a, long long b)
{
	long long r = 1;
	while (b)
	{
		if (b & 1)
			r = r * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return r;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	int m;
	cin >> n >> m;
	vector<long long> fact(m + 1, 1);
	for (int i = 1; i <= m; i++)
		fact[i] = fact[i - 1] * i % MOD;
	if (n == 0)
	{
		cout << (modpow(2, m) * fact[m]) % MOD << "\n";
		return 0;
	}
	int maxMask = 1 << n; // n<=20
	vector<int> freqS(maxMask, 0), freqT(maxMask, 0);
	vector<int> Scol(m, 0), Tcol(m, 0);
	string s;
	for (int i = 0; i < n; i++)
	{
		cin >> s; // S_i
		for (int j = 0; j < m; j++)
			if (s[j] == '1')
				Scol[j] |= (1 << i);
	}
	for (int i = 0; i < n; i++)
	{
		cin >> s; // T_i
		for (int j = 0; j < m; j++)
			if (s[j] == '1')
				Tcol[j] |= (1 << i);
	}
	for (int j = 0; j < m; j++)
	{
		++freqS[Scol[j]];
		++freqT[Tcol[j]];
	}
	int fullMask = (1 << n) - 1;
	vector<char> vis(maxMask, 0);
	long long ans = 1;
	for (int mask = 0; mask < maxMask; ++mask)
	{
		if (vis[mask])
			continue;
		int comp = mask ^ fullMask;
		if (vis[comp])
			continue; // 已处理
		vis[mask] = vis[comp] = 1;
		long long a = freqS[mask];
		long long a2 = (comp == mask ? 0 : freqS[comp]);
		long long b = freqT[mask];
		long long b2 = (comp == mask ? 0 : freqT[comp]);
		if (a + a2 != b + b2)
		{
			cout << 0 << "\n";
			return 0;
		}
		long long groupSize = a + a2; // = b + b2
		ans = ans * fact[groupSize] % MOD;
	}
	cout << ans % MOD << "\n";
	return 0;
}