#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
inline int add(int a, int b)
{
    a += b;
    return a >= MOD ? a - MOD : a;
}
inline int mul(long long a, long long b) { return int(a * b % MOD); }
int C[205][205];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string l;
    cin>>l;
    long long k, m;
    cin >> k >> m;
    int n = l.size();
    for (int i = 0; i <= n; i++)
    {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++)
            C[i][j] = add(C[i - 1][j - 1], C[i - 1][j]);
    }
    int all[205] = {0}, le[205] = {0}, eq[205] = {0}, les[205] = {0};
    for (int i = 0; i <= n; i++)
        all[i] = C[n][i];
    int ones = 0;
    for (int i = 0; i < n; i++)
        if (l[i] == '1')
        {
            int rem = n - i - 1;
            for (int t = 0; t <= rem; t++)
                le[ones + t] = add(le[ones + t], C[rem][t]);
            ++ones;
        }
    le[ones] = add(le[ones], 1);
    eq[ones] = 1;
    for (int i = 0; i <= n; i++)
        les[i] = (le[i] - eq[i] + MOD) % MOD;
    if (k == 1)
    {
        int ans = 0;
        for (int i = 0; i <= n; i++)
            ans = add(ans, le[i]);
        cout << ans << "\n";
        return 0;
    }
    if (m <= 5)
    {
        int M = m, sz = M + 2;
        vector<vector<int>> T(sz, vector<int>(sz));
        if (ones + ones <= m)
            T[0][0] = 1;
        for (int y = 0; y <= M; y++)
            if (ones + y <= m)
                T[0][1 + y] = les[y];
        for (int x = 0; x <= M; x++)
            for (int y = 0; y <= M; y++)
                if (x + y <= m)
                    T[1 + x][1 + y] = all[y];
        vector<int> vec(sz);
        vec[0] = 1;
        for (int y = 0; y <= M; y++)
            vec[1 + y] = les[y];
        long long e = k - 1;
        vector<vector<int>> P = T, R(sz, vector<int>(sz));
        for (int i = 0; i < sz; i++)
            R[i][i] = 1;
        while (e)
        {
            if (e & 1)
            {
                vector<vector<int>> S(sz, vector<int>(sz));
                for (int a = 0; a < sz; a++)
                    for (int b = 0; b < sz; b++)
                        if (R[a][b])
                        {
                            int v = R[a][b];
                            for (int c = 0; c < sz; c++)
                                if (P[b][c])
                                    S[a][c] = add(S[a][c], mul(v, P[b][c]));
                        }
                R.swap(S);
            }
            vector<vector<int>> S(sz, vector<int>(sz));
            for (int a = 0; a < sz; a++)
                for (int b = 0; b < sz; b++)
                    if (P[a][b])
                    {
                        int v = P[a][b];
                        for (int c = 0; c < sz; c++)
                            if (P[b][c])
                                S[a][c] = add(S[a][c], mul(v, P[b][c]));
                    }
            P.swap(S);
            e >>= 1;
        }
        vector<int> nv(sz);
        for (int a = 0; a < sz; a++)
            if (vec[a])
            {
                int va = vec[a];
                for (int b = 0; b < sz; b++)
                    if (R[a][b])
                        nv[b] = add(nv[b], mul(va, R[a][b]));
            }
        vec.swap(nv);
        int ans = 0;
        for (int i = 0; i < sz; i++)
            ans = add(ans, vec[i]);
        cout << ans << "\n";
        return 0;
    }
    auto runDP = [&](bool prefix)
    { vector<int> tight(n+1), loose(n+1); 
        tight[ones]=1; 
        for(int i=0;i<=n;i++) loose[i]=les[i]; 
        for(long long step=2; step<=k; ++step){ 
            vector<int> nt(n+1), nl(n+1); 
            if(prefix){ 
                vector<int> preT(n+1), preL(n+1); 
                preT[0]=tight[0]; preL[0]=loose[0]; 
                for(int i=1;i<=n;i++){ 
                    preT[i]=add(preT[i-1], tight[i]);
                    preL[i]=add(preL[i-1], loose[i]); 
                } int lim=m-ones;
                 if(lim>=0){ 
                    if(lim>n) lim=n; 
                    nt[ones]=preT[lim]; 
                } 
                    for(int y=0;y<=n;y++) 
                    if(m-y>=0){ 
                        int L=m-y; 
                        if(L>n) L=n; 
                        int sumT=preT[L]; 
                        if(les[y]) nl[y]=add(nl[y], mul(sumT, les[y]));
                         int sumL=preL[L]; 
                         nl[y]=add(nl[y], mul(sumL, all[y])); } } 
                         else { for(int x=0;x<=n;x++) 
                            if(tight[x]){ 
                                int tx=tight[x];
                                 if(x+ones<=m) nt[ones]=add(nt[ones], tx);
                                  for(int y=0;y<=n;y++) 
                                  if(les[y] && x+y<=m) nl[y]=add(nl[y], mul(tx, les[y])); 
                                } 
                                for(int x=0;x<=n;x++) 
                                if(loose[x]){ 
                                    int lx=loose[x]; 
                                    for(int y=0;y<=n;y++) 
                                    if(x+y<=m) nl[y]=add(nl[y], mul(lx, all[y])); } 
                                } 
                                tight.swap(nt);
                                 loose.swap(nl);} 
                                 int ans=0; 
                                 for(int i=0;i<=n;i++) 
                                 ans=add(ans, add(tight[i], loose[i])); cout<<ans<<"\n"; 
                                };
    long double v1 = (long double)n * n * k, v2 = (long double)n * k;
    if (v1 <= 1e7)
    {
        runDP(false);
        return 0;
    }
    if (v2 <= 1e7)
    {
        runDP(true);
        return 0;
    }
    cout << 0 << "\n";
}
