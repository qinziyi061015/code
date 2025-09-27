#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

// 计算 n! 中素数 p 的指数
static inline int64 exp(int n, int p)
{
	int64 e = 0;
	while (n)
	{
		n /= p;
		e += n;
	}
	return e;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	long long M;
	cin>>T>>M;
	// 预筛素数到 5000 (最大 sum C_i)
	const int mx = 5000;
	vector<int> primes;
	vector<int> is(mx + 1, 1);
	is[0] = is[1] = 0;
	for (int i = 2; i <= mx; i++)
		if (is[i])
		{
			primes.push_back(i);
			if (1LL * i * i <= mx)
				for (long long j = 1LL * i * i; j <= mx; j += i)
					is[(int)j] = 0;
		}
	while (T--)
	{
		int N;
		cin >> N;
		vector<int> C(N);
		int S = 0;
		for (int i = 0; i < N; i++)
		{
			cin >> C[i];
			S += C[i];
		}
		long long ans = 1 % M;
		for (int p : primes)
		{
			if (p > S)
				break;
			long long e = exp(S, p);
			for (int x : C)
				e -= exp(x, p); // multinomial exponent
			// ans*=p^e mod M
			long long base = p % M, res = 1 % M;
			long long k = e;
			while (k)
			{
				if (k & 1)
					res = (__int128)res * base % M;
				base = (__int128)base * base % M;
				k >>= 1;
			}
			ans = (__int128)ans * res % M;
			if (ans == 0)
			{
			} // early zero optional (could break if want)
		}
		cout << ans << "\n";
	}
	return 0;
}