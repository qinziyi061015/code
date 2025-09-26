#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	long long x,y,z; if(!(cin>>x>>y>>z)) return 0;
	long long M = max({x,y,z});
	int cntOdd = ((M - x) & 1) + ((M - y) & 1) + ((M - z) & 1);
	// 若以 T=M 目标时只有 1 个奇差值(即 cntOdd==1) 不可一次性配对，需要把目标提高 1（改变所有差值奇偶性）
	long long T = (cntOdd == 1) ? M + 1 : M; // 这样差值奇数个数为 0 或 2，总能用一条(1,1)操作消去奇性
	// 最少操作次数 = (总需增加羽毛数)/2 = ( (T-x)+(T-y)+(T-z) ) /2 = (3T - (x+y+z))/2
	long long ans = (3*T - (x + y + z)) / 2;
	cout << ans << '\n';
	return 0;
}