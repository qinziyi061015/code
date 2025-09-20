#include <bits/stdc++.h>
using namespace std;
static inline long long cost(long long ai, int j){
    long long lo = 1LL<<j; 
    long long mod = 1LL<<(j+1); 
    long long t=ai%mod;
    if(t>=lo) return 0LL;     
    return lo-(ai%lo);         
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; 
    cin>>T;
    const int MAXB=31;
    while(T--){
        int n,q; 
        cin>>n>>q;
        vector<long long>a(n);
        for(int i=0;i<n;i++) cin>>a[i];
        vector<long long> best(MAXB, (long long)4e18);
        for(int i=0;i<n;i++){
            long long ai=a[i];
            for(int j=0;j<MAXB;j++){
                long long c=cost(ai,j);
                if(c<best[j]) best[j]=c;
            }
        }
        sort(best.begin(), best.end());
        vector<long long> pre(MAXB+1,0);
        for(int i=0;i<MAXB; i++){
            long long val=best[i];
            if(val>(long long)4e18/2) val=(long long)4e18/2;
            pre[i+1]=min((long long)4e18/2,pre[i]+val);
        }
        while(q--){
            long long b; 
            cin>>b;
            int k=upper_bound(pre.begin(), pre.end(), b)-pre.begin()-1;
            cout<<k<<'\n';
        }
    }
    return 0;
}