#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
    {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> sets(n);
        vector<vector<int>> pos(m + 1);
        for (int i = 0; i < n; ++i)
        {
            int tmp;
            cin >> tmp;
            sets[i].resize(tmp);
            for (int j = 0; j < tmp; ++j)
            {
                int x;
                cin >> x;
                sets[i][j] = x;
                pos[x].push_back(i);//x元素被几个集合覆盖
            }
        }
        int f = 0;
        for (int x = 1; x <= m; ++x)
            if (pos[x].empty())
            {
                f = 1;
                break;
            }
        if (f)
        {
            cout << "NO\n";
            continue;
        }

        vector<char> forced(n, 0);
        for (int x = 1; x <= m; ++x)
            if (pos[x].size() == 1)
            {
                forced[pos[x][0]] = 1;//必选的集合
            }
        vector<char> cov(m + 1, 0);
        for (int i = 0; i < n; ++i)
            if (forced[i])
            {
                for (int x : sets[i])
                    cov[x] = 1;//已经覆盖
            }
        int un = 0;
        for (int x = 1; x <= m; ++x)
            if (!cov[x])
            {
                un = 1;
                break;
            }

        if (un)//有至少一个元素被两个集合包含，1， 2 ，12 三中
        {
            cout << "YES\n";
        }
        else
        {
            int free = 0;
            for (int i = 0; i < n; ++i)
                if (!forced[i])
                    ++free;
            cout << (free >= 2 ? "YES\n" : "NO\n");//2^2
        }
    }
    return 0;
}
