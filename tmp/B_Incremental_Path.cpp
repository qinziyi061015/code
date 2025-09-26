// 简洁竞赛版：前缀递推 + set 跳黑
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100000 + 5;
int T,n,m,fin[MAXN];
long long a[MAXN];
string s; set<long long> blk;
inline void mv(long long &x,char c){ ++x; if(c=='B') while(blk.count(x)) ++x; }
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr);
	if(!(cin>>T)) return 0;
	while(T--){
		cin>>n>>m>>s; s=' '+s; // 1-index
		blk.clear();
		for(int i=1;i<=m;i++){cin>>a[i]; blk.insert(a[i]);}
		fin[0]=1;
		for(int i=1;i<=n;i++){
			long long cur=fin[i-1];
			if(i>1){ mv(cur,s[i-1]); fin[i]=cur; mv(cur,s[i]); }
			else { fin[i]=1; mv(cur,s[i]); }
			blk.insert(cur);
		}
		cout<<blk.size()<<'\n';
		for(auto v:blk) cout<<v<<' '; cout<<'\n';
	}
	return 0;
}
#define int long long

