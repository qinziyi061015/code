#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;

using mint = atcoder::modint998244353;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector dp(k + 1, vector(n + 1, mint(0)));
    mint m_inv = mint(1) / m;
    dp[0][0] = 1;
    for(int i = 0; i < k; i++) {//次数
        for(int j = 0; j <= n; j++) {//到达的位置
            if(j == n) {
                dp[i + 1][j] += dp[i][j];
                continue;
            }
            for(int l = 1; l <= m; l++) {//选出的数
                int nx = j + l;
                if(nx > n) nx = n - (nx - n);
                dp[i + 1][nx] += dp[i][j] * m_inv;
            }
        }
    }
    cout << dp.back().back().val() << endl;
}
