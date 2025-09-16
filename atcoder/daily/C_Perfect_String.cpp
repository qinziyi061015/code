#include<bits/stdc++.h>
using namespace std;
string s;
unordered_map<char,int> mp;
int solve(){
    int f=0,f1=0;
    for(int i=0;i<s.size();i++){
        if(mp[s[i]]) {
            return 0;
        
        }
        else mp[s[i]]=1;
        if(s[i]>='A'&&s[i]<='Z') f=1;
        if(s[i]>='a'&&s[i]<='z') f1=1;
    }
    return f&&f1;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
    
    cin>>s;
    cout<<(solve()?"Yes":"No");
	return 0;
}