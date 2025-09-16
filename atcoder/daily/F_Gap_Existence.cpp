#include<bits/stdc++.h>
using namespace std;
unordered_map<int,int> mp;
int solve(){
    int n,k,a;
    cin>>n>>k;
    if(k==0) return 1;
    for(int i=1;i<=n;i++){
        cin>>a;
        if(mp[a+k]==1||mp[a-k]==1) return 1;
        mp[a]=1;
    }
    return 0;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
    cout<<(solve()?"Yes":"No");
	return 0;
}