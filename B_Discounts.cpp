#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; 
    cin>>T;
    while(T--){
        int n=0,k=0,tot=0,free = 0; 
        cin>>n>>k;
        vector<int> a(n);
        vector<int> b(k);
        for(int i=0;i<n;i++) cin>>a[i];
        for(int i=0;i<k;i++) cin>>b[i];
        sort(a.begin(), a.end(), greater<int>());
        sort(b.begin(), b.end());
        for(int i=0;i<a.size();i++) tot += a[i];
        int l=0;
        int id1=0;
        while(id1<k&&b[id1]==1){
            if(l<n){
                free+=a[l];
                l++;
            }
            id1++;
        }
        for(int j=id1;j<k; j++){
            int len=b[j];
            if(l+len-1<n){
                free+=a[l+len-1];
                l+=len;
            } else {
                break;
            }
        }
        cout <<(tot - free) << '\n';
    }
    return 0;
}
