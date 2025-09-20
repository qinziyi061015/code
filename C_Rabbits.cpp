#include <bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int i; 
	cin>>i;
	while(i--){
		int n; string s; 
		cin>>n>>s;
		int f=1;
		vector<int> pos; pos.reserve(n);
		for(int i=0;i<n;i++){
			if(s[i]!='0') continue;
			if(!(i-1>=0 && s[i-1]=='0')&&!(i+1<n&&s[i+1]=='0')) pos.push_back(i);
		}
		int m= pos.size();
		int idx = 0;
		while(f&&idx<m){
			int j=idx;
			while(j+1<m&&pos[j+1]==pos[j]+2)j++; 
			int k=j-idx+1;
			vector<char> mt(k, 0);
			auto required = [&](int i){ int p=pos[idx+i];return!(p==0 || p==n-1); };
			for(int i=0; i<k&&f;i++){
				if(!required(i)) continue; 
				if(mt[i]) continue; 
				if(i+1<k&&!mt[i+1]&&required(i+1)){
					mt[i]=mt[i+1]=1;i++; 
				} else if(i-1>=0&&!mt[i-1]){
					mt[i]=mt[i-1]=1;
				} else if(i+1<k&&!mt[i+1]){
					mt[i]=mt[i+1]=1;i++;
				} else {
					f=0;break;
				}
			}
			idx=j+1;
		}
		cout << (f?"YES":"NO")<<'\n';
	}
	return 0;
}