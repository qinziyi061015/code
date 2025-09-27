#include <bits/stdc++.h>
using namespace std;
using int64 = long long;



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; 
    cin>>T;
    while(T--){
        long long m; 
        cin >> m;
        if(m <= 1){
            cout << "Lose!\n";
            continue;
        }
        // 下界 L：最小 n 使 n(n-1)/2 >= m
        long double disc = 1.0L + 8.0L * m;
        long long L = (long long)ceil( (1.0L + sqrt(disc)) / 2.0L );
        long long R = 2 * m - 2;
        if(L > R){
            cout << "Lose!\n";
        }else{
            cout << L << ' ' << R << "\n";
        }
    }
    return 0;
}