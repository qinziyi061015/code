#include <bits/stdc++.h>
#define int long long
using namespace std;
const int p = 1e9+7;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; 
    cin>>T;
    while(T--){
        int n=0,ans=0; 
        cin>>n;
        vector<int> a(n+1);
        for(int i=1;i<=n;i++) cin>>a[i];
        vector<vector<int>> f(n+1, vector<int>(n+1, 0));
        f[0][0]=1;//以0结尾，以0结尾的个数,枚举dp,n<300,9000次，100case，9e5次
        for(int i=1;i<=n;i++){
            int now=a[i];
            vector<vector<int> > tmpf = f;
            for(int l=0;l<=n;l++){
                for(int r=0;r<=n;r++){
                    int cnt = f[l][r];
                    if(!cnt) continue;
                    if(now>=l){
                        tmpf[now][r]=(tmpf[now][r]+cnt)%p;
                    } else if(now>=r){
                        tmpf[l][now]=(tmpf[l][now]+cnt)%p;
                    }
                }
            }
            f=tmpf;
        }
        for(int l=0;l<=n;l++) {
            for(int r=0;r<=n;r++){
                ans=(ans+f[l][r])%p;
            }
        }   
       cout<<ans%p<<"\n";
    }
    return 0;
}
