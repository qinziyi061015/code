#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
    int n,m,k;
    
    cin>>n>>m>>k;
    vector<vector<int> > v(n+1,vector<int>(0,0));
    vector<int> ans;
    while(k--){
        int a,b;
        cin>>a>>b;
        v[a].push_back(b);
        if(v[a].size()==m){
            ans.push_back(a);
        }
    }
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<' ';
    }
	return 0;
}