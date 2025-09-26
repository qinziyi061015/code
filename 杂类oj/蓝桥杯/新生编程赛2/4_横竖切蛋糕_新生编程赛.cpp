#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	long long N; if(!(cin>>N)) return 0;
	// 设横切 h 刀, 竖切 v=N-h 刀, 形成 (h+1)*(v+1) 块
	// 该函数关于 h 为 -(h^2) + (N)h + (N+1), 在抛物线顶点附近 h≈N/2 取得最大
	// 直接取 floor(N/2) 与 ceil(N/2) 作为 h 即可
	long long h1 = N/2;              // floor
	long long h2 = (N+1)/2;          // ceil
	long long ans = max( (h1+1)*(N-h1+1), (h2+1)*(N-h2+1) );
	cout<<ans<<"\n";
	return 0;
}