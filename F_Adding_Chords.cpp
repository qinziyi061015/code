
#include <bits/stdc++.h>
using namespace std;

// 使用两个线段树，分别检测两种交叉模式：
// 1) a < l < b < r  — 在左端点区间 (a,b) 上查询最大 r 是否 > b。
// 2) l < a < r < b  — 在右端点区间 (a,b) 上查询最小 l 是否 < a。
// 因为题意保证所有 A_i、B_i 互不相同，两个树都是点更新（每个位置至多更新一次），区间查询。

struct SegMax
{
	int n, SZ;
	vector<int> t;
	void init(int n_)
	{
		n = n_;
		SZ = 1;
		while (SZ < n)
			SZ <<= 1;
		t.assign(2 * SZ, 0);
	}
	void point_max(int p, int v)
	{
		int i = p + SZ;
		t[i] = max(t[i], v);
		for (i >>= 1; i; i >>= 1)
			t[i] = max(t[i << 1], t[i << 1 | 1]);
	}
	int range_max(int l, int r)
	{
		if (l > r)
			return 0;
		int L = l + SZ, R = r + SZ, res = 0;
		while (L <= R)
		{
			if (L & 1)
				res = max(res, t[L++]);
			if (!(R & 1))
				res = max(res, t[R--]);
			L >>= 1;
			R >>= 1;
		}
		return res;
	}
};
struct SegMin
{
	int n, SZ;
	vector<int> t;
	const int INF = 1e9;
	void init(int n_)
	{
		n = n_;
		SZ = 1;
		while (SZ < n)
			SZ <<= 1;
		t.assign(2 * SZ, INF);
	}
	void point_min(int p, int v)
	{
		int i = p + SZ;
		t[i] = min(t[i], v);
		for (i >>= 1; i; i >>= 1)
			t[i] = min(t[i << 1], t[i << 1 | 1]);
	}
	int range_min(int l, int r)
	{
		if (l > r)
			return INF;
		int L = l + SZ, R = r + SZ, res = INF;
		while (L <= R)
		{
			if (L & 1)
				res = min(res, t[L++]);
			if (!(R & 1))
				res = min(res, t[R--]);
			L >>= 1;
			R >>= 1;
		}
		return res;
	}
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, Q;
	if (!(cin >> N >> Q))
		return 0;
	vector<pair<int, int>> qs(Q);
	vector<int> AL;
	AL.reserve(Q);
	vector<int> BR;
	BR.reserve(Q);
	for (int i = 0; i < Q; ++i)
	{
		int a, b;
		cin >> a >> b;
		qs[i] = {a, b};
		AL.push_back(a);
		BR.push_back(b);
	}

	sort(AL.begin(), AL.end());
	AL.erase(unique(AL.begin(), AL.end()), AL.end());
	sort(BR.begin(), BR.end());
	BR.erase(unique(BR.begin(), BR.end()), BR.end());

	auto idxL = [&](int a)
	{ return int(lower_bound(AL.begin(), AL.end(), a) - AL.begin()); };
	auto idxR = [&](int b)
	{ return int(lower_bound(BR.begin(), BR.end(), b) - BR.begin()); };

	SegMax stL;
	stL.init((int)AL.size()); // 左端点 -> 最大右端点
	SegMin stR;
	stR.init((int)BR.size()); // 右端点 -> 最小左端点

	for (int i = 0; i < Q; ++i)
	{
		int a = qs[i].first, b = qs[i].second;
		bool bad = false;

		// 检查 a < l < b < r：在左端点 (a,b) 的索引范围查询最大 r 是否 > b
		int lL = int(upper_bound(AL.begin(), AL.end(), a) - AL.begin());
		int rL = int(lower_bound(AL.begin(), AL.end(), b) - AL.begin()) - 1;
		if (lL <= rL)
		{
			int mx = stL.range_max(lL, rL);
			if (mx > b)
				bad = true;
		}

		// 检查 l < a < r < b：在右端点 (a,b) 的索引范围查询最小 l 是否 < a
		if (!bad)
		{
			int lR = int(upper_bound(BR.begin(), BR.end(), a) - BR.begin());
			int rR = int(lower_bound(BR.begin(), BR.end(), b) - BR.begin()) - 1;
			if (lR <= rR)
			{
				int mn = stR.range_min(lR, rR);
				if (mn < a)
					bad = true;
			}
		}

		if (bad)
		{
			cout << "No\n";
		}
		else
		{
			cout << "Yes\n";
			// 接受该弦，更新两棵树
			int pL = idxL(a);
			stL.point_max(pL, b);
			int pR = idxR(b);
			stR.point_min(pR, a);
		}
	}

	return 0;
}