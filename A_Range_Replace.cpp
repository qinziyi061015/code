#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin>>N;
    vector<int> A(N + 1);
    for (int i = 1; i <= N; ++i)
        cin >> A[i];

    // total count of each value
    vector<int> tot(N + 1, 0), seen(N + 1, 0);
    for (int i = 1; i <= N; ++i)
        ++tot[A[i]];

    long long ans = 1; // 原样（任选一个不改变的区间）
    for (int i = 1; i <= N; ++i)
    {
        int v = A[i];
        bool isRunStart = (i == 1) || (A[i] != A[i - 1]);
        // 先处理段起点的贡献，再累计 seen
        if (isRunStart)
        {
            int suffixLen = N - i + 1;
            int occGeq = tot[v] - seen[v]; // 在 [i..N] 中 v 的出现次数
            ans += (long long)(suffixLen - occGeq);
        }
        ++seen[v];
    }

    cout << ans << '\n';
    return 0;
}