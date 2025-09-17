#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; 
    cin>>T;
    while(T--){
        int n; cin>>n;
        vector<int> a(n);
        for(int i=0;i<n;i++) cin>>a[i];
        bool f = 1;
        vector<int> r = a;
        for(int k=n;k>=1;k--){
            bool found = false;
            for(int s=0;s+k-1 < n; s++){
                bool can = 1;
                for(int j=s;j<=s+k-1;j++){
                    if(r[j] <= 0){ can = false; break; }
                }
                if(can){
                    for(int j=s;j<=s+k-1;j++) r[j]--;
                    found = 1;
                    break;
                }
            }
            if(!found){ 
                f = 0; 
                break;
             }
        }
        cout<<(f?"YES":"NO")<<"\n";
    }
    return 0;
}
