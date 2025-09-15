#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 题目：Price Tags
// 思路（中文）：
// 对于固定的整数 x (>1)，第 i 件商品的新价格为 v = ceil(c_i / x)。
// 我们原来有一堆已有的价签，其面额就是原始的 c_j（每个面额有若干张）。
// 对于固定 x，统计每个可能的新面额 v 需要多少张价签 need[v]，已有可用的价签数量为 have[v]=freq[c==v]。
// 那么需要新印刷的价签数为 sum_v max(0, need[v] - have[v])。总收入 = sum_v v * need[v] - y * printed_count。
// 我们要在所有 x>1 中寻找最大值。
// 关键在于如何快速计算 need[v] 对于每个 x。
// 注意到 need[v] = number of c in ((v-1)*x, v*x]。因此如果我们有原价频率的前缀和 pref[],
// 则 need[v] = pref[min(v*x, maxC)] - pref[(v-1)*x].
// 对于固定 x，我们只需要枚举 v = 1 .. ceil(maxC / x)，共约 maxC/x 项。对所有 x 从 2 到 maxC+1，总复杂度约为 maxC * H(maxC) ~ 2e5 * log 2e5，能在 2 秒内通过。

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
	cin>>T;
    while(T--){
        int n; ll y; cin>>n>>y;
        vector<int> c(n);
        int maxC = 0;
        for(int i=0;i<n;i++){ cin>>c[i]; maxC = max(maxC, c[i]); }

        

        vector<int> freq(maxC+1, 0);
        for(int v: c) freq[v]++;
        vector<int> pref(maxC+1, 0);
        for(int v=1; v<=maxC; v++) pref[v] = pref[v-1] + freq[v];

        ll best = LLONG_MIN;
        // iterate x from 2 to maxC+1 (x > maxC gives same result as x = maxC+1)
        for(int x=2; x<=maxC+1; x++){
            ll printed = 0;
            ll total_price = 0;
            // v ranges where (v-1)*x < = maxC
            int v = 1;
            while((v-1) * 1LL * x <= maxC){
                int L = (v-1) * x + 1;
                int R = min(maxC, v * x);
                if(L > R){ v++; continue; }
                int need = pref[R] - pref[L-1];
                if(need){
                    total_price += 1LL * v * need;
                    if(v <= maxC) {
                        int have = freq[v];
                        if(need > have) printed += (need - have);
                    } else {
                        printed += need; // v>maxC have[v]=0
                    }
                }
                v++;
            }
            ll income = total_price - printed * y;
            if(income > best) best = income;
        }

        cout<<best<<"\n";
    }
    return 0;
}
