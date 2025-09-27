
#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
struct Node { int ch[2]; Node(){ ch[0]=ch[1]=-1;} };
int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int N; int64 M; cin>>N>>M;  vector<int> A(N); int mx=0; for(int i=0;i<N;i++){ cin>>A[i]; mx=max(mx,A[i]); }
	// 使用 limit = M-1 (包含上界) 进行数位DP
	int64 limit = M-1; // M>=1
	int64 need = max<int64>(mx, (limit>=0?limit:0));
	int B=1; while((1ll<<B) <= need) ++B; // 使用 B 位覆盖 [0, M-1] 与所有 A_i
	vector<Node> trie(1); 
	vector<int> dep; dep.push_back(0);
	for(int v: A){ int u=0; for(int b=B-1;b>=0;--b){ int bit=(v>>b)&1; if(trie[u].ch[bit]==-1){ trie[u].ch[bit]=trie.size(); trie.emplace_back(); dep.push_back(dep[u]+1);} u=trie[u].ch[bit]; } }
	int nodes = trie.size();
	struct dpv{ long long sum; long long cnt; bool vis[2]; dpv(){ sum=cnt=0; vis[0]=vis[1]=false; } };
	vector<dpv> dp(nodes);
	// 递归函数
	function<pair<long long,long long>(int,int)> dfs = [&](int u, int tight)->pair<long long,long long>{
		if(dp[u].vis[tight]) return {dp[u].sum, dp[u].cnt};
		int d = dep[u];
		if(d==B){ // 已确定所有位
			dp[u].vis[tight]=true; dp[u].cnt=1; dp[u].sum=0; return {0,1};
		}
	int pos = B - d - 1; long long w = 1ll<<pos;
	int lb = (limit>>pos)&1; // 该位 limit 的限制（仅当 tight=1 生效）
		long long totsum=0, totcnt=0;
		for(int i=0; i<=1; ++i){
			if(tight && i>lb) continue; // 超过 limit 前缀
			int nt = tight && (i==lb);
			int child = trie[u].ch[i];
			long long add = 0; int nextNode = child;
			if(child==-1){ // 需走另一个存在的分支并产生 cost w
				int other = trie[u].ch[i^1];
				if(other==-1){ // 理论上不应发生（构造全长）
					continue;
				}
				add = w; nextNode = other;
			}
			pair<long long,long long> res = dfs(nextNode, nt);
			long long subSum = res.first; long long subCnt = res.second;
			totsum += subSum + add*subCnt;
			totcnt += subCnt;
		}
		dp[u].vis[tight]=true; dp[u].sum=totsum; dp[u].cnt=totcnt;
		return {totsum,totcnt};
	};
	auto ans = dfs(0,1).first; // 仅统计 x < M
	cout<<ans<<"\n";
	return 0;
}

