#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 998244353;
int add(int a,int b){
	 a+=b; 
	 if(a>=MOD) a-=MOD; 
	 return a;
 }
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T; 
	cin>>T;
	while(T--){
		int n; cin>>n;
		vector<int> a(n+1), b(n+1);
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++) cin>>b[i];
		array<int,2> f0 = {0,0}, f1 = {0,0};
		f0[0]=1; 
		f0[1]=1; 
		for(int i=2;i<=n;i++){
			f1[0]=f1[1]=0;

			for(int t=0;t<=1;t++){
				for(int s=0;s<=1;s++){
					if(f0[t]==0) continue;
					int al,bl,ar,br;
					if(t==0){
						al=a[i-1];
						bl=b[i-1];
					}
					else {
						al=b[i-1];
						bl=a[i-1];
					}
					
					if(s==0){
						ar=a[i];
						br=b[i];
					}
					else {
						ar=b[i];
						br=a[i];
					}
					
			
					if(al <= ar && bl <= br){
						f1[s] = add(f1[s], f0[t]);
					}
				}
			}
			f0 = f1;
		}
		int ans = 0;
		if(n==1) ans = add(1,1); else ans = add(f0[0], f0[1]);

		cout<<ans%MOD<<"\n";
	}
	return 0;
}

