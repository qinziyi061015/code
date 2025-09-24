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
        string s;
        cin >> n >> s;
        vector<int> p(n + 1, 0);
        for (int i = 1; i <= n; i++)
            if (s[i - 1] == '1')
                p[i] = i;
        int f = 0;
        for (int i = 1; i <= n;)
        {
            if (s[i - 1] == '0')
            {
                int j = i;
                while (j <= n && s[j - 1] == '0')
                    ++j;

                if (j - i == 1)
                {
                    f = 1;
                    break;
                }
                for (int k = i; k < j - 1; ++k)
                    p[k] = k + 1;
                p[j - 1] = i;
                i = j;
            }
            else
            {
                ++i;
            }
        }
        if (f)
        {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
        for (int i = 1; i <= n; i++)
        {
            if (i > 1)
                cout << ' ';
            cout << p[i];
        }
        cout << '\n';
    }
    return 0;
}