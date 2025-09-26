#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; 
    cin>>T;
    while(T--){
        int n; 
        cin>>n;
        vector<vector<int>> adj(n+1);
        vector<int> in(n+1,0);
        for(int i=0;i<n-1;i++){
            int u,v,x,y; 
            cin>>u>>v>>x>>y;
            if(x>y){
                adj[v].push_back(u);
                in[u]++;
            }else if(y>x){
                adj[u].push_back(v);
                in[v]++;
            }
            
        }
        //oiwiki toposort
        queue<int> S;
        for(int i=1;i<=n;i++) if(in[i]==0) S.push(i);
        vector<int> L;
        while(!S.empty()){
            int u = S.front(); 
            S.pop();
            L.push_back(u);
            for(int v: adj[u]){
                if(--in[v]==0) S.push(v);
            }
        }
        unordered_map<int,int> mp;
        for(int i=0;i<n;i++){
            mp[L[i]] = i+1; 
        }
        for(int i=1;i<=n;i++){
            cout<<mp[i]<<' ';
        }
        cout<<"\n";
    }
    return 0;
}
