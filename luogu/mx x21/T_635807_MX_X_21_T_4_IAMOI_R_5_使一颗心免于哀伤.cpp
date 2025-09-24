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
        string s;
        cin >> s;
        int B = 0;
        for (char c : s)
            if (c == '1')
                ++B;
        int W = n - B;

        if (W == 0)
        { // 只有黑棋
            cout << "Sunday\n";
            continue;
        }
        if (B == 0)
        { // 只有白棋
            cout << "Robin\n";
            continue;
        }

        // 统计环上的黑白段数
        int SB = 0, SW = 0;
        for (int i = 0; i < n; ++i)
        {
            int p = (i - 1 + n) % n;
            if (s[i] == '1' && s[p] == '0')
                ++SB;
            if (s[i] == '0' && s[p] == '1')
                ++SW;
        }

        // 若黑棋仅一段，知更鸟可一招清空黑棋
        if (SB == 1)
        {
            cout << "Robin\n";
            continue;
        }
        if (SW == 1)
        {
            cout << "Sunday\n";
            continue;
        }

        // 一般情形：当两色均存在且段数均>=2时，比较总数量 B 与 W
        // 直觉：双方每步都能让对方的段数合并一次，而谁的棋子总量更少，谁更可能先被清空
        // 实践规则：B > W 则 Robin，否则 Sunday
        if (B > W)
            cout << "Robin\n";
        else
            cout << "Sunday\n";
    }
    return 0;
}