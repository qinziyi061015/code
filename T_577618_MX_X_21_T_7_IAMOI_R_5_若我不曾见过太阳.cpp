#include <bits/stdc++.h>
using namespace std;

static inline bool sorted(const vector<int> &a)
{
    int n = (int)a.size() - 1; // 1-based
    for (int i = 1; i <= n; ++i)
        if (a[i] != i)
            return false;
    return true;
}

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
        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];

        if (sorted(a))
        {
            cout << 0 << "\n";
            continue;
        }

        int step = 0, answer = -1;
        for (int k = n - 1; k >= 1; --k)
        {
            ++step;
            // 按值桶化 + 组号稳定串接：
            // 1) 记录每个值当前所在位置
            vector<int> pos(n + 1);
            for (int i = 1; i <= n; ++i)
                pos[a[i]] = i;
            // 2) 每组的写指针和目标数组
            vector<int> ptr(k + 1), b(n + 1);
            for (int g = 1; g <= k; ++g)
                ptr[g] = g;
            // 3) 依值从小到大，将值放入其组的下一个位置（稳定）
            for (int v = 1; v <= n; ++v)
            {
                int i = pos[v];
                int g = ((i - 1) % k) + 1;
                int p = ptr[g];
                b[p] = v;
                ptr[g] = p + k;
            }
            a.swap(b);

            if (sorted(a))
            {
                answer = step;
                break;
            }
        }
        if (answer == -1)
            answer = step; // k=1 必定有序
        cout << answer << "\n";
    }
    return 0;
}