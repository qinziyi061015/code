#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T; 
    cin>>T;
	while(T--){
		long long a,b,n;cin>>a>>b>>n;
		if(a==n || b==n){ cout<<"No\n"; continue; }
		if(a==0 && b==0){ cout<<(n==0?"No":"Yes")<<"\n"; continue; }
		if(a==0 || b==0){
			long long m = max(a,b);
			if(n>=m && n % m == 0) cout<<"No\n"; else cout<<"Yes\n";
			continue;
		}
		long long x=a, y=b; 
		while(y < n){
			long long z = x + y; 
			if(z == n){ y = z; break; }
			x = y; y = z;
			if(y > n) break;
		}
		if(y == n) cout<<"No\n"; else cout<<"Yes\n";
	}
	return 0;
}