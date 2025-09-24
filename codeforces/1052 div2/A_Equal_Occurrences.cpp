
#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        vector<int> freq(n + 1, 0);
        for (int x : a)
            ++freq[x];
        vector<int> counts;
        counts.reserve(n);
        int maxc = 0;
        for (int v = 1; v <= n; ++v)
            if (freq[v] > 0)
            {
                counts.push_back(freq[v]);
                maxc = max(maxc, freq[v]);
            }
        int ans = 0;
        for (int f = 1; f <= maxc; ++f)
        {
            int tmp = 0;
            for (int c : counts)
                if (c >= f)
                    ++tmp;
            ans = max(ans, tmp * f);
        }
        cout << ans << '\n';
    }
    return 0;
}
