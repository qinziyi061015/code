// E. Yet Another MEX Problem
// Maintain for each potential mex K: w_K = F(K) - s[K], where
// F(K) = count of elements > K processed so far = i - sum_{v<=K} cnt_v,
// s[K] = F(K) at time last[K] (last occurrence index), so that w_K counts only after last[K].
// For fixed i, answer = max over valid K of w_K.
// Valid K are precisely the indices K in the prefix-min chain of last[0..curMex] where last[K] equals the prefix minimum at K
// (including K = curMex with last[K] = -INF). Track this chain as "owners" via a linked list, and keep minimal H[K] = sumUpTo(K) - s[K]
// among owners in a segment tree with operations: range add +1 on [x..n] when processing a[i]=x, point assign H[x] on updates,
// toggle membership by assigning +INF for non-owners and H[K] for owners. Answer at i is i - minH.

#include <bits/stdc++.h>
using namespace std;

struct BIT {
	int N; vector<int> f;
	BIT() {}
	BIT(int n) { init(n); }
	void init(int n){ N=n; f.assign(N+1,0);} // 1..N
	void add(int idx,int v){ for(int i=idx;i<=N;i+=i&-i) f[i]+=v; }
	int sumPrefix(int idx){ int s=0; for(int i=idx;i>0;i-=i&-i) s+=f[i]; return s; }
};

struct SegTree {
	struct Node{ long long mn, add; };
	int N; vector<Node> st;
	const long long INF = (long long)4e18;
	SegTree() {}
	SegTree(int n){ init(n); }
	void init(int n){ N=n; st.assign(4*N+4, {INF,0}); }
	void apply(int p, long long v){ st[p].mn += v; st[p].add += v; }
	void push(int p){ if(st[p].add!=0){ apply(p<<1, st[p].add); apply(p<<1|1, st[p].add); st[p].add=0; } }
	void pull(int p){ st[p].mn = min(st[p<<1].mn, st[p<<1|1].mn); }
	void rangeAdd(int p,int l,int r,int ql,int qr,long long v){ if(ql>r||qr<l) return; if(ql<=l&&r<=qr){ apply(p,v); return;} push(p); int m=(l+r)>>1; rangeAdd(p<<1,l,m,ql,qr,v); rangeAdd(p<<1|1,m+1,r,ql,qr,v); pull(p);} 
	void rangeAdd(int l,int r,long long v){ if(l>r) return; rangeAdd(1,0,N-1,l,r,v);} // indices 0..N-1
	void pointAssign(int p,int l,int r,int idx,long long val){ if(l==r){ st[p].mn = val; st[p].add=0; return;} push(p); int m=(l+r)>>1; if(idx<=m) pointAssign(p<<1,l,m,idx,val); else pointAssign(p<<1|1,m+1,r,idx,val); pull(p);} 
	void pointAssign(int idx,long long val){ pointAssign(1,0,N-1,idx,val); }
	long long queryMin(){ return st[1].mn; }
};

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);

	int T; if(!(cin>>T)) return 0;
	while(T--){
		int n; cin>>n; vector<int>a(n+1); for(int i=1;i<=n;++i) cin>>a[i];
		int Kmax = n; // K in [0..n]
		const long long NEG_INF = LLONG_MIN/4;

		// last[K] = last occurrence index (1..i), or -1 if unseen
		vector<long long> last(Kmax+1, -1);
		vector<long long> s(Kmax+1, 0); // snapshot F(K) at last[K]
		vector<long long> H(Kmax+1, 0); // H[K] = sumUpTo(K) - s[K]
		vector<char> inOwner(Kmax+1, 0);
		vector<int> prevO(Kmax+1, -1), nextO(Kmax+1, -1);
		int head=-1, tail=-1;

		auto addOwner = [&](int k, SegTree &seg){
			if(k<0 || k> Kmax) return;
			if(inOwner[k]) return;
			inOwner[k]=1; prevO[k]=tail; nextO[k]=-1; if(tail!=-1) nextO[tail]=k; else head=k; tail=k;
			seg.pointAssign(k, H[k]);
		};
		auto removeOwner = [&](int k, SegTree &seg){
			if(!inOwner[k]) return;
			int p=prevO[k], q=nextO[k];
			if(p!=-1) nextO[p]=q; else head=q;
			if(q!=-1) prevO[q]=p; else tail=p;
			prevO[k]=nextO[k]=-1; inOwner[k]=0;
			seg.pointAssign(k, seg.INF);
		};

		BIT bit(Kmax+1); // map value v (0..n) to idx v+1
		SegTree seg(Kmax+1); // indices 0..Kmax

		// Initialize owners with curMex=0 (unseen) as tail record
		int curMex = 0;
		// H[0] = sumUpTo(0) initially 0
		H[0]=0; addOwner(0, seg);

		vector<long long> ans(n+1, 0);
		for(int i=1;i<=n;++i){
			int x = a[i];
			// 1) Update counts
			bit.add(x+1, 1);
			int sumUpToX = bit.sumPrefix(x+1); // counts of <= x
			// 2) Range add +1 to all K >= x
			seg.rangeAdd(x, Kmax, 1);

			// 3) Update s[x], H[x]
			long long Fx = i - (long long)sumUpToX; // F(x)
			s[x] = Fx;
			H[x] = (long long)sumUpToX * 2 - i; // = sum - s[x]
			if(inOwner[x]) seg.pointAssign(x, H[x]);

			// 4) Update last[x] and owners chain
			bool wasUnseen = (last[x] == -1);
			last[x] = i;
			if(inOwner[x]){
				// If previous owner exists and decreasing violated, remove x
				int p = prevO[x];
				if(p != -1 && last[x] >= last[p]){
					removeOwner(x, seg);
				}
			}

			// 5) If we just saw curMex, advance and add new unseen owner
			if(wasUnseen && x == curMex){
				while(curMex <= Kmax && last[curMex] != -1) ++curMex;
				if(curMex <= Kmax){
					// H[curMex] = sumUpTo(curMex)
					int sumUpToK = bit.sumPrefix(curMex+1);
					s[curMex] = 0;
					H[curMex] = (long long)sumUpToK; 
					addOwner(curMex, seg);
				}
			}

			long long minH = seg.queryMin();
			long long best = (long long)i - minH;
			if(best < 0) best = 0; // safety
			ans[i] = best;
		}

		for(int i=1;i<=n;++i){ if(i>1) cout<<' '; cout<<ans[i]; } cout<<'\n';
	}
	return 0;
}