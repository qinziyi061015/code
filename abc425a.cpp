#include <bits/stdc++.h>
using namespace std;
int main() {
    long long N;
    if (!(cin >> N)) return 0;
    long long ans = 0;
    for (long long i = 1; i <= N; ++i) {
        long long term = i * i * i;
        if (i & 1) ans -= term;  // (-1)^i  (i 为奇数时是 -1)
        else       ans += term;  // i 偶数时是 +1
    }
    cout << ans << "\n";
    return 0;
}