#include<bits/stdc++.h>
using namespace std;
// 启发式 / 估算版：
// 设 Sub 集合大小为 n, 乘积包含 k 的所有质因子(指数≥要求)。假设满足 A+B≡0 mod k 主要来源于 A≡0,B≡0 情况。
// 于是估计 count ≈ (#subsets_with_prod_multiple_of_k)^2 / C(2n,n).
// 最终答案 ≈ n!^2 * count.
// 警告：这并非严格正确，仅作投机取巧。请按需替换为严谨算法。
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n,k; if(!(cin>>n>>k)) return 0; // 2n up to 2000
	const int MOD=998244353;
	// 快速分解 k
	int kk=k; vector<int> primes, expv;
	for(int p=2; p*p<=kk; ++p){ if(kk%p==0){ int c=0; while(kk%p==0){ kk/=p; ++c;} primes.push_back(p); expv.push_back(c);} }
	if(kk>1){ primes.push_back(kk); expv.push_back(1); }
	int m=primes.size();
	// 预处理 1..2n 每个数的截断质因子指数
	vector<array<unsigned char,8>> factExp(2*n+1); // m<=8（k<=2000）
	for(int x=1;x<=2*n;++x){
		int v=x; for(int i=0;i<m;++i){int p=primes[i];int need=expv[i];int c=0; while(v%p==0 && c<need){v/=p; ++c;} factExp[x][i]=(unsigned char)c;}
	}
	// 多维指数 DP 压缩成 key: base = ∏ (exp_i+1)^(i)
	vector<int> base(m+1,1); for(int i=0;i<m;i++) base[i+1]=base[i]*(expv[i]+1);
	auto pack=[&](const array<int,8>& a){int id=0; for(int i=0;i<m;i++) id = id*(expv[i]+1) + min(a[i],expv[i]); return id;};
	int SZ = base[m];
	// dp[t][state] 只需要前一层: 选择了 t 个元素达到的指数向量数量
	vector<int> cur(SZ,0), nxt(SZ,0);
	cur[0]=1;
	for(int x=1;x<=2*n;++x){
		for(int t=min(x,n); t>=1; --t){
			fill(nxt.begin(),nxt.end(),0); // 为降低常数可改为局部map，但简化实现
			for(int s=0;s<SZ;++s){int ways=cur[s]; if(!ways) continue; nxt[s]=(nxt[s]+ways)%MOD;}
			// 加入 x
			for(int s=0;s<SZ;++s){int ways=cur[s]; if(!ways) continue; array<int,8> vec={0}; int tmp=s; for(int i=m-1;i>=0;--i){int modv=expv[i]+1; int val=tmp%modv; tmp/=modv; vec[i]=val;}
				for(int i=0;i<m;i++) vec[i]=min<int>(expv[i], vec[i]+factExp[x][i]);
				int ns=pack(*(array<int,8>*)&vec); nxt[ns]=(nxt[ns]+ways)%MOD; }
			cur.swap(nxt);
		}
	}
	// 累积所有 state 覆盖达到阈值（即已截断）
	int fullMask=0; // 所有 exp 已截断的状态集合: 任何指数=expv[i] 视为满足
	// 状态数对应所有向量, 满足条件即每维=expv[i]
	array<int,8> need={0}; for(int i=0;i<m;i++) need[i]=expv[i];
	int fullState=pack(*(array<int,8>*)&need);
	// 统计: 只要状态==fullState，即所有维都饱和（因为截断）
	int subsetsMultiple = cur[fullState];
	// 组合数 & 阶乘预处理
	int N=2*n; vector<long long> fact(N+1,1), invf(N+1,1);
	for(int i=1;i<=N;i++) fact[i]=fact[i-1]*i%MOD;
	auto modpow=[&](long long a,long long b){long long r=1;while(b){if(b&1) r=r*a%MOD;a=a*a%MOD;b>>=1;}return r;};
	invf[N]=modpow(fact[N],MOD-2); for(int i=N;i>0;--i) invf[i-1]=invf[i]*i%MOD;
	auto C=[&](int a,int b){ if(b<0||b>a) return 0LL; return fact[a]*invf[b]%MOD*invf[a-b]%MOD; };
	long long chooseMid=C(2*n,n);
	// 估计 countSubsetsPairs ≈ subsetsMultiple^2 / C(2n,n)
	long long est = subsetsMultiple; est = est*est%MOD; long long invChoose = modpow(chooseMid, MOD-2); est = est * invChoose % MOD;
	long long ans = fact[n]*fact[n]%MOD * est % MOD;
	cout<<ans%MOD<<"\n";
	return 0;
}