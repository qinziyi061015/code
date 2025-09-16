#include<bits/stdc++.h>
using namespace std;
unordered_map<char,int> mp;

int main(){
	ios::sync_with_stdio(0);cin.tie(0);
    int n,q;
    cin>>n>>q;
    vector<pair<int,int> > loc(n+q+105);
    for(int i=n;i>=1;i--){
        loc[n-i+1]={i,0};
    }
    int now=n;
    while(q--){
        int p;
        char pp;
        int ppp;
        cin>>p;
        if(p==1){
            now++;
            cin>>pp;
            if(pp=='U'){
                loc[now]={loc[now-1].first,loc[now-1].second+1};
            }
            if(pp=='D'){
                loc[now]={loc[now-1].first,loc[now-1].second-1};
            }
            if(pp=='L'){
                loc[now]={loc[now-1].first-1,loc[now-1].second};
            }
            if(pp=='R'){
                loc[now]={loc[now-1].first+1,loc[now-1].second};
            }
            // for(int i=1;i<=now;i++){
            //     cout<<loc[i].first<<' '<<loc[i].second<<"U\n";
            // }
        }
        else{
            cin>>ppp;
            cout<<loc[now+1-ppp].first<<' '<<loc[now+1-ppp].second<<'\n';
        }
    }
    
	return 0;
}