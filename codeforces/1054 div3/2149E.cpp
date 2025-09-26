#include <bits/stdc++.h>
using namespace std;
int n, k, l, r;
vector<int> a;
long long at_most(int K){
    if(K<0) return 0LL; 
    static vector<int> comp; comp.clear(); comp.reserve(n);
    for(int x: a) comp.push_back(x);
    sort(comp.begin(),comp.end()); comp.erase(unique(comp.begin(),comp.end()),comp.end());
    int m = comp.size();
    vector<int> freq(m,0);
    auto id=[&](int v){ return int(lower_bound(comp.begin(),comp.end(),v)-comp.begin()); };
    long long ans=0; int lid=0, distinct=0;
    for(int rid=0; rid<n; ++rid){
        int idx=id(a[rid]); if(++freq[idx]==1) ++distinct;
        while(distinct>K){ int idx2=id(a[lid]); if(--freq[idx2]==0) --distinct; ++lid; }
        int len = rid - lid + 1; if(len<l) continue; int upto = min(len, r); ans += (long long)max(0, upto - l + 1);
    }
    return ans;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--)
	{
		cin >> n >> k >> l >> r;
		a.clear();
		for (int i = 0; i < n; i++)
		{
			int tmp = 0;
			cin >> tmp;
			a.push_back(tmp);
		}

		long long ans = at_most(k) - at_most(k - 1);
		cout << ans << "\n";
	}
	return 0;
}