#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	long long N; if(!(cin>>N)) return 0; // 0 <= N < 1e6
	if(N<0 || N>=1000000){ cout<<"NO"; return 0; }
	int d[6]; for(int i=5;i>=0;--i){ d[i]=N%10; N/=10; }
	int s1=d[0]+d[1]+d[2]; int s2=d[3]+d[4]+d[5];
	cout<<(s1==s2?"YES":"NO");
	return 0;
}