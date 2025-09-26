#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int N; if(!(cin>>N)) return 0;
	if(N<1 || N>12){ cout<<"??"; return 0; }
	int q=(N-1)/3+1; // 1..3 ->1, 4..6 ->2, 7..9 ->3, 10..12 ->4
	cout<<'Q'<<q;
	return 0;
}