
#include <bits/stdc++.h>
using namespace std;

static inline vector<int> build_offsets(int n)
{
    vector<int> off;
    off.reserve(n);
    int rem = n - 1;
    if (rem == 0)
    {
        off.push_back(0);
        return off;
    }
    while (rem > 0)
    {
        int p = 1 << (31 - __builtin_clz(rem));
        for (int x = p - 1; x >= rem - p + 1; --x)
            off.push_back(x);
        for (int x = rem; x >= p; --x)
            off.push_back(x);
        rem -= p;
    }
    off.push_back(0);
    return off;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
    {
        long long l, r;
        cin >> l >> r;
        int n = int(r - l + 1);

        vector<int> off = build_offsets(n);
        vector<long long> a(n);
        long long sum = 0;
        for (int i = 0; i < n; ++i)
        {
            a[i] = l + off[i];
            sum += (a[i] | (l + i));
        }

        cout << sum << '\n';
        for (int i = 0; i < n; ++i)
        {
            if (i)
                cout << ' ';
            cout << a[i];
        }
        cout << '\n';
    }
    return 0;
}
