#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        int fu = 0, zero = 0;
        for (int i = 0, x; i < n; ++i)
        {
            cin >> x;
            if (x == 0)
                ++zero;
            else if (x == -1)
                ++fu;
        }

        int ans = zero + ((fu % 2) ? 2 : 0);
        cout << ans << '\n';
    }
    return 0;
}