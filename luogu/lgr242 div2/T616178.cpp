
#include <bits/stdc++.h>
using namespace std;

struct node
{
	unordered_map<long long, int> mp;
	int ask(int a, int b)
	{
		if (a > b)
			swap(a, b);
		long long key = ((long long)a << 32) | b;
		auto it = mp.find(key);
		if (it != mp.end())
			return it->second;
		cout << "? " << a << " " << b << "\n";
		cout.flush();
		int v;
		if (!(cin >> v))
			exit(0);
		mp[key] = v;
		return v;
	}
} qc;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, p;
	if (!(cin >> n >> p))
		return 0;
	int N = 2 * n;
	int base = qc.ask(p, p);
	auto searchRight = [&]() -> int
	{ if(p==N) return -1; if(qc.ask(p,p+1)==base) return p+1; int l=p+1,r=N,ans=p; while(l<=r){ int mid=(l+r)>>1; if(qc.ask(p,mid)>base){ ans=mid; l=mid+1;} else r=mid-1; } if(ans==N) return -1; int q=ans+1; if(q> N) return -1; if(qc.ask(p,q)==base) return q; return -1; };
	auto searchLeft = [&]() -> int
	{ if(p==1) return -1; if(qc.ask(p-1,p)==base) return p-1; int l=1,r=p-1,ans=p; while(l<=r){ int mid=(l+r)>>1; if(qc.ask(mid,p)>base){ ans=mid; r=mid-1;} else l=mid+1; } if(ans==1) return -1; int q=ans-1; if(q<1) return -1; if(qc.ask(q,p)==base) return q; return -1; };
	int res = searchRight();
	if (res == -1)
		res = searchLeft();
	if (res == -1)
		res = p;
	cout << "! " << res << "\n";
	cout.flush();
}