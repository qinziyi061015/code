#include <bits/stdc++.h>
using namespace std;

struct FastScanner {
	static const int S = 1 << 20; int idx = 0, size = 0; char buf[S];
	inline char gc(){ if(idx>=size){ size=(int)fread(buf,1,S,stdin); idx=0; if(!size) return EOF; } return buf[idx++]; }
	bool readInt(int &out){ char c=gc(); if(c==EOF) return false; int s=1,x=0; while(c!='-'&&(c<'0'||c>'9')){ c=gc(); if(c==EOF) return false; } if(c=='-'){ s=-1; c=gc(); } for(; c>='0'&&c<='9'; c=gc()) x=x*10+(c-'0'); out=x*s; return true; }
	bool readString(string &s){ char c=gc(); if(c==EOF) return false; while(c=='\n'||c=='\r'||c==' '||c=='\t'){ c=gc(); if(c==EOF) return false; } s.clear(); while(c!=EOF&&c!='\n'&&c!='\r'&&c!=' '&&c!='\t'){ s.push_back(c); c=gc(); } return true; }
} In;

struct FastPrinter { static const int S=1<<20; int idx=0; char buf[S]; ~FastPrinter(){ flush(); } inline void pc(char c){ if(idx>=S) flush(); buf[idx++]=c; } inline void flush(){ if(idx){ fwrite(buf,1,idx,stdout); idx=0; } } inline void printLL(long long x){ if(x==0){ pc('0'); return; } if(x<0){ pc('-'); x=-x; } char s[24]; int n=0; while(x){ s[n++]=char('0'+(x%10)); x/=10; } while(n--) pc(s[n]); } } Out;

static long long solve_fast(const string &S){
	int n = (int)S.size();
	// 1) 无边界子串（单段）
	long long ans = 0;
	vector<int> runL; runL.reserve(n);
	for(int i=0;i<n;){ int j=i; while(j<n && S[j]==S[i]) ++j; long long L=j-i; ans += L*(L+1)/2; runL.push_back((int)L); i=j; }

	// 2) 边界 B[1..m]
	vector<int> B; B.reserve(n);
	for(int i=1;i<=n-1;++i) if(S[i-1]!=S[i]) B.push_back(i);
	int m=(int)B.size(); if(m==0) return ans;

	// 3) A[u] = sum_{t=1..u} (-1)^t * B[t]  (1-based u)
	vector<long long> A(m+1,0);
	for(int u=1;u<=m;++u){ long long term = ( (u&1) ? -1LL : +1LL ) * (long long)B[u-1]; A[u]=A[u-1]+term; }

	// 4) 构建按奇偶拆分的序列与前缀和
	vector<int> idxOdd, idxEven; idxOdd.reserve((m+1)/2); idxEven.reserve(m/2);
	for(int u=1;u<=m;++u){ if(u&1) idxOdd.push_back(u); else idxEven.push_back(u); }

	auto buildSeq = [&](const vector<int>& idx){
		int sz=(int)idx.size();
		vector<long long> H(sz); // H[u] per parity chain
		vector<int> Bb(sz), Next(sz); // boundary position and next boundary pos or n
		vector<long long> PS(sz+1,0); // prefix sum of (Next - B)
		for(int i=0;i<sz;++i){ int u=idx[i]; long long Hu = ((u&1)? (-2LL*A[u] - (long long)B[u-1]) : (2LL*A[u] - (long long)B[u-1])); H[i]=Hu; Bb[i]=B[u-1]; Next[i]=(i+1<sz? B[idx[i+1]-1] : n); PS[i+1]=PS[i]+(long long)(Next[i]-Bb[i]); }
		return tuple<vector<long long>,vector<int>,vector<int>,vector<long long>>(move(H),move(Bb),move(Next),move(PS));
	};

	vector<long long> HOdd; vector<int> BOdd, NOdd; vector<long long> PSOdd;
	{
		auto tup = buildSeq(idxOdd);
		HOdd = std::move(std::get<0>(tup));
		BOdd = std::move(std::get<1>(tup));
		NOdd = std::move(std::get<2>(tup));
		PSOdd = std::move(std::get<3>(tup));
	}
	vector<long long> HEven; vector<int> BEven, NEven; vector<long long> PSEven;
	{
		auto tup = buildSeq(idxEven);
		HEven = std::move(std::get<0>(tup));
		BEven = std::move(std::get<1>(tup));
		NEven = std::move(std::get<2>(tup));
		PSEven = std::move(std::get<3>(tup));
	}

	vector<int> posOdd(m+1,-1), posEven(m+1,-1);
	for(int i=0;i<(int)idxOdd.size();++i) posOdd[idxOdd[i]]=i;
	for(int i=0;i<(int)idxEven.size();++i) posEven[idxEven[i]]=i;

	// 5) 遍历每个边界段（以边界 T 结束的 run），从右往左扫描 l，维护 jEnd 与 curMin
	for(int T=1; T<=m; ++T){
		int lStart = (T==1? 1 : B[T-2]+1);
		int lEnd   = B[T-1];
		long long base = (long long)(- ((T&1)? -1: +1) ) * 2LL * A[T-1]; // - sT * 2*A[T-1]
		if(T&1){
			int i0 = posOdd[T]; int sz=(int)HOdd.size();
			long long curMin = (long long)4e18; int jEnd = i0-1;
			for(int l=lEnd; l>=lStart; --l){
				long long C = (long long)(l-1) + base; // C = (l-1) - sT*2*A[T-1]
				while(jEnd+1<sz){ long long cand = min(curMin, HOdd[jEnd+1]); if(cand + C >= 0){ curMin=cand; ++jEnd; } else break; }
				if(jEnd>=i0){ long long add = PSOdd[jEnd+1] - PSOdd[i0]; ans += add; }
			}
		}else{
			int i0 = posEven[T]; int sz=(int)HEven.size();
			long long curMin = (long long)4e18; int jEnd = i0-1;
			for(int l=lEnd; l>=lStart; --l){
				long long C = (long long)(l-1) + base;
				while(jEnd+1<sz){ long long cand = min(curMin, HEven[jEnd+1]); if(cand + C >= 0){ curMin=cand; ++jEnd; } else break; }
				if(jEnd>=i0){ long long add = PSEven[jEnd+1] - PSEven[i0]; ans += add; }
			}
		}
	}
	return ans;
}

#ifdef DEBUG
static long long solve_bruteforce(const string &S){
	int n=(int)S.size(); long long ans=0;
	for(int l=0;l<n;++l){
		int ones=0, zeros=0;
		for(int r=l;r<n;++r){
			if(S[r]=='1') ++ones; else ++zeros;
			if(S[l]=='1') ans += (ones>=zeros);
			else ans += (zeros>=ones);
		}
	}
	return ans;
}
#endif

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T; if(!In.readInt(T)) return 0;
	while (T--) {
		string S; In.readString(S);
		long long ans = solve_fast(S);
#ifdef DEBUG
		if((int)S.size()<=200){
			long long brute=solve_bruteforce(S);
			if(brute!=ans){
				cerr << "[T5 DEBUG] MISMATCH! S=" << S << " fast=" << ans << " brute=" << brute << "\n";
			}
		}
#endif
		Out.printLL(ans);
		Out.pc('\n');
	}
	Out.flush();
	return 0;
}