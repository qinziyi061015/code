#include <bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr);
	int t; 
	cin>>t;
	while(t--){
		int x, y; 
		cin>>x>>y;
		if (y>x) {
			cout<<"2\n";
		} else if (x==y) {
			cout<<"-1\n";
		} else { // x > y
			if (y>=2&&x-y>=2) cout<<"3\n";
			else cout<<"-1\n";
		}
	}
	return 0;
}
