#include <bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T; if(!(cin>>T)) return 0;
	while(T--){
		int N,K; cin>>N>>K;
		if(N==1){
			if(K==1){ cout<<1<<"\n"; }
			else{ cout<<-1<<"\n"; }
			continue;
		}
		if(K<=1){ cout<<-1<<"\n"; continue; }
		if(K> N){ cout<<-1<<"\n"; continue; }

		// Construct: [K, K-1, ..., 1, K+1, K+2, ..., N]
		vector<int> ans; ans.reserve(N);
		for(int i=K;i>=1;i--) ans.push_back(i);
		for(int v=K+1; v<=N; v++) ans.push_back(v);
		for(int i=0;i<N;i++){
			if(i) cout << ' ';
			cout << ans[i];
		}
		cout << '\n';
	}
	return 0;
}