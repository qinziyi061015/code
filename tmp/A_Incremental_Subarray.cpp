
#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T; 
	cin>>T;
	while (T--) {
		int n, m,mx=-1;
		cin >> n >> m;
		vector<int> a(m);
		for (int i = 0; i < m; i++) cin >> a[i];
		for (int i = 0; i + 1 < m; i++) {
			if (a[i+1] == a[i] + 1) continue;   
			if (a[i+1] == 1) {
				mx=max(mx,a[i])  ;    
			} 
		}
		int ans = 0;
		if (mx==-1) {
			ans = n - a[m-1] + 1;
			if (ans < 0) ans = 0;
		} else {
			ans=1;
        }
		cout << ans << '\n';
	}
	return 0;
}