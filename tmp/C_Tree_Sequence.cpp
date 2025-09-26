// Count good sequences satisfying: for every adjacent i, (B_i = i+1) or (B_{i+1} = i).
// We count completions of A with -1 wildcards.

#include <bits/stdc++.h>
using namespace std;

static const int MOD = 998244353;
inline int addmod(int a, int b)
{
	a += b;
	if (a >= MOD)
		a -= MOD;
	return a;
}
inline int mulmod(long long a, long long b) { return int((a * b) % MOD); }

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int N;
	if (!(cin >> N))
		return 0;
	vector<int> A(N + 1);
	for (int i = 1; i <= N; i++)
		cin >> A[i];

	if (N == 1)
	{
		// No adjacent constraint; any value in [1..N] is 1 choice.
		// If A1==-1 -> 1 way; else either 1 if A1 in [1..1] else 0 (but input guarantees 1..N or -1).
		cout << 1 << '\n';
		return 0;
	}

	auto weights = [&](int i)
	{
		// Return weights for choosing L: (A[i]=i-1), R: (A[i]=i+1), O: other values
		long long wL = 0, wR = 0, wO = 0;
		bool hasL = (i - 1 >= 1);
		bool hasR = (i + 1 <= N);
		if (A[i] == -1)
		{
			if (hasL)
				wL = 1;
			if (hasR)
				wR = 1;
			wO = N - (int)hasL - (int)hasR;
		}
		else
		{
			if (hasL && A[i] == i - 1)
				wL = 1;
			else if (hasR && A[i] == i + 1)
				wR = 1;
			else
				wO = 1;
		}
		return array<int, 3>{(int)(wL % MOD), (int)(wR % MOD), (int)(wO % MOD)};
	};

	int dp0 = 1, dp1 = 0; // dp0: not forcing x_i; dp1: forcing x_i (i.e., A[i]=i-1)

	for (int i = 1; i <= N - 1; i++)
	{
		auto w = weights(i);
		int wL = w[0], wR = w[1], wO = w[2];
		int ndp0 = 0, ndp1 = 0;

		// From dp0: free at i
		if (dp0)
		{
			if (wR)
				ndp0 = addmod(ndp0, mulmod(dp0, wR)); // choose R -> satisfy pair i
			int to1 = (wL + wO) % MOD;				  // choose L or O -> need force x_{i+1}
			if (to1)
				ndp1 = addmod(ndp1, mulmod(dp0, to1));
		}

		// From dp1: must choose L at i
		if (dp1)
		{
			if (wL)
			{
				// choose L -> pair i still unsatisfied by y_i, so force x_{i+1}
				ndp1 = addmod(ndp1, mulmod(dp1, wL));
			}
		}

		dp0 = ndp0;
		dp1 = ndp1;
	}

	// At i = N: settle the last forced requirement on x_N (if any). No y_N.
	auto wN = weights(N);
	int wLN = wN[0], wON = wN[2]; // R at N is invalid or zero
	int ans = 0;
	if (dp0)
	{
		int sum = (wLN + wON) % MOD; // any choice at N
		if (sum)
			ans = addmod(ans, mulmod(dp0, sum));
	}
	if (dp1)
	{
		if (wLN)
			ans = addmod(ans, mulmod(dp1, wLN)); // must choose L
	}

	cout << ans << '\n';
	return 0;
}
