#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if(!(cin>>T)) return 0;
    while(T--){
        int n; cin>>n;
        vector<int> a(n+1);
		vector<int> missing;
		vector<char> ac(n+1, 0);
        for(int i=1;i<=n;i++) cin>>a[i];
        vector<char> present(n+1, 0);
        vector<int> zeros;
        for(int i=1;i<=n;i++){
            if(a[i]==0) zeros.push_back(i);
            else present[a[i]] = 1;
        }
        for(int x=1;x<=n;x++) if(!present[x]) missing.push_back(x);
        for(int i=1;i<=n;i++) if(a[i]>0 && a[i]==i) ac[i]=1;
        if(zeros.size()==1 && missing.size()==1){
            if(zeros[0]==missing[0]) ac[zeros[0]] = 1;
        }
        int l = -1, r = -1;
        for(int i=1;i<=n;i++){
            if(!ac[i]){
                if(l==-1) l = i;
                r = i;
            }
        }
        if(l==-1){
            cout<<0<<"\n";
        }else{
            cout<< (r - l + 1) <<"\n";
        }
    }
    return 0;
}
