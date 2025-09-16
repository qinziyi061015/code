#include<bits/stdc++.h>
using namespace std;
unordered_map<char,int> mp;
bool solve(){
    int n;
    cin>>n;
    vector<int> o(n+1);
    for(int i=1;i<=n;i++){
        int l,r;
        cin>>l>>r;
        o[l]++;
        o[r]++;
    }
    for(int i=1;i<=n;i++){
        if(o[i]==n){
            return 1;
        }
    }
    return 0;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
    cout<<(solve()?"Yes":"No");
    
	return 0;
}