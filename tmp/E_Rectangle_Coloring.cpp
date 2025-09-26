#include <bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T; if(!(cin>>T)) return 0;
	while(T--){
		int N; cin >> N;
		int M = N - 2;
		vector<long long> U(M), D(M), L(M), R(M);
		for(int i=0;i<M;i++) cin >> U[i];
		for(int i=0;i<M;i++) cin >> D[i];
		for(int i=0;i<M;i++) cin >> L[i];
		for(int i=0;i<M;i++) cin >> R[i];

		auto fx = [](const vector<long long>& a){
			long long x = LLONG_MAX, y = LLONG_MAX;
			for(long long v: a){
				if(v < x){ y = x; x = v; }
				else if(v < y){ y = v; }
			}
			return x + y;
		};

		long long ans = 0;
		ans += fx(U);
		ans += fx(D);
		ans += fx(L);
		ans += fx(R);
		cout << ans << '\n';
	}
	return 0;
}