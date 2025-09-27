#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int len; cin>>len; string bits; cin>>bits; // bits[0] 最高位
	const int MOD=998244353;
	// 状态编号: (ti<<1)|tj  ti=1 表示 i 已经严格小于前缀, tj 同理
	struct Node{ long long c, p1, p2, p3, p4; } cur[4], nxt[4];
	cur[0]={1,0,0,0,0}; for(int i=1;i<4;i++) cur[i]={0,0,0,0,0};
	for(char c: bits){
		int nb=c-'0'; for(int i=0;i<4;i++) nxt[i]={0,0,0,0,0};
		for(int st=0; st<4; ++st){
			if(!cur[st].c) continue;
			int ti=st>>1, tj=st&1; auto &old=cur[st];
			for(int ib=0; ib<2; ++ib){ if(!ti && ib>nb) continue; int nti = ti || (ib<nb);
				for(int jb=0; jb<2; ++jb){ if(!tj && jb>nb) continue; int ntj = tj || (jb<nb);
					int nst=(nti<<1)|ntj; int x=ib^jb; auto &nw=nxt[nst]; long long t=old.c;
					nw.c = (nw.c + t) % MOD;
					if(x==0){
						nw.p1 = (nw.p1 + 2*old.p1)%MOD;
						nw.p2 = (nw.p2 + 4*old.p2)%MOD;
						nw.p3 = (nw.p3 + (8*old.p3)%MOD)%MOD;
						nw.p4 = (nw.p4 + (16*old.p4)%MOD)%MOD;
					}else{
						nw.p1 = (nw.p1 + 2*old.p1 + t)%MOD;
						nw.p2 = (nw.p2 + 4*old.p2 + 4*old.p1 + t)%MOD;
						nw.p3 = (nw.p3 + (8*old.p3)%MOD + (12*old.p2)%MOD + (6*old.p1)%MOD + t)%MOD;
						nw.p4 = (nw.p4 + (16*old.p4)%MOD + (32*old.p3)%MOD + (24*old.p2)%MOD + (8*old.p1)%MOD + t)%MOD;
					}
				}
			}
		}
		for(int i=0;i<4;i++) cur[i]=nxt[i];
	}
	long long ans=0; for(int st=0; st<4; ++st) ans = (ans + cur[st].p4)%MOD;
	cout<<ans%MOD<<"\n";
	return 0;
}