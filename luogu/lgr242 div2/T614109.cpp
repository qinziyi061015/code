#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n,k; cin>>n>>k; string s; cin>>s;
	if(k>n-1){ cout<<0<<"\n"; return 0; }
	int R=1; 
	for(int i=1;i<n;i++) if(s[i]!=s[i-1]) ++R; 
	int ans = max(0, min(k, n - R) -max(0, k - (R - 1)) + 1);
	cout<<ans<<"\n";
	return 0;
}