// 重新设计算法：
// 我们需要计算不同的字符串序列 (s_0, ..., s_N)，其中通过在前一字符串任意位置插入一个字符构成，最终得到固定 T。
// 逆向视角：从 T 逐步删除字符到空串。若当前剩余的是子序列 T|S（S 为保留下标集合的升序排列），
// 在该“压缩串”中，同一 run（连续相同字符）内删除哪个具体位置得到的下一串完全相同，因此这整段 run 只贡献 1 个转移到 S\{p}（任选 run 内一个位置 p）。
// 关键：即使当前压缩串所有相邻字符都不同（无 run 长度>=2），仍不能直接用 (|S|)!，因为未来删除掉中间分隔字符后，原来不相邻的相同字符会合并形成 run，导致多个删除顺序产生同一字符串序列（例："aba" 应为 5 而不是 6）。
// 因此只有当 T 整体所有字符均互不相同（全局频次<=1）时才能直接返回 N!。
// 通用解：子集 DP。dp[mask] 表示“保留下标集合=mask” 对应的剩余压缩串到空串的不同删除序列条数。
// 递推：dp[mask] = sum_{每个 run R 于 压缩串 T|mask} dp[mask ^ (1<<posR)]，选 run 中任一位置 posR（取第一个即可）。
// 基础：dp[0] = 1。
// 最终答案是 dp[ (1<<N)-1 ]。
// 复杂度 O(N * 2^N)，N<=22 可行（~92M 基本操作以内）。

#include <bits/stdc++.h>
using namespace std;
using int64 = long long; const int MOD = 998244353;

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int N; cin>>N; string T; cin>>T;
	// 若全局无重复字符，可直接返回 N!（所有插入顺序相互区别且不会后续合并）
	array<int,26> freq{}; bool uni=true; for(char c: T){ if(++freq[c-'a']>1) uni=false; }
	if(uni){
		int64 ans=1; for(int i=2;i<=N;i++) ans=ans*i%MOD; cout<<ans<<"\n"; return 0;
	}
	int M = 1<<N; vector<int> dp(M,0); dp[0]=1;
	// 按子集大小递增
	for(int mask=1; mask<M; ++mask){
		// 提取顺序下标形成“压缩串”
		// 找 runs
		int prevPos=-1; // 用于收集 vector 加速（可直接扫描）
		vector<int> idx; idx.reserve(__builtin_popcount(mask));
		for(int i=0;i<N;i++) if(mask>>i & 1) idx.push_back(i);
		int sz = (int)idx.size();
		for(int p=0; p<sz; ){ int q=p+1; while(q<sz && T[idx[q]]==T[idx[p]]) ++q; // run [p,q)
			// 删除 run 内任意一个 -> 选择 run 第一个 idx[p]
			int pos = idx[p]; int sub = mask ^ (1<<pos);
			dp[mask] += dp[sub]; if(dp[mask]>=MOD) dp[mask]-=MOD;
			p = q;
		}
	}
	cout<<dp[M-1]%MOD<<"\n";
	return 0;
}
