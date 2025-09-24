
#include<bits/stdc++.h>
//321312
//43214123
using namespace std;
int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        for(int i=n;i>=1;i--) cout<<i<<' ';
        cout<<n<<' ';
        for(int i=1;i<n;i++) cout<<i<<' ';
        cout<<'\n';
    }
    return 0;
}