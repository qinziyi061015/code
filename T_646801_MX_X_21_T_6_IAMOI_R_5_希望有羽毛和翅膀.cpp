#include <bits/stdc++.h>
using namespace std;

struct FastScanner
{
    static const int S = 1 << 20;
    int idx = 0, size = 0;
    char buf[S];
    inline char gc()
    {
        if (idx >= size)
        {
            size = (int)fread(buf, 1, S, stdin);
            idx = 0;
            if (!size)
                return EOF;
        }
        return buf[idx++];
    }
    bool readInt(int &out)
    {
        char c = gc();
        if (c == EOF)
            return false;
        int sgn = 1, x = 0;
        while (c != '-' && (c < '0' || c > '9'))
        {
            c = gc();
            if (c == EOF)
                return false;
        }
        if (c == '-')
        {
            sgn = -1;
            c = gc();
        }
        for (; c >= '0' && c <= '9'; c = gc())
            x = x * 10 + (c - '0');
        out = x * sgn;
        return true;
    }
    bool readString(string &s)
    {
        char c = gc();
        if (c == EOF)
            return false;
        while (c == '\n' || c == '\r' || c == ' ' || c == '\t')
        {
            c = gc();
            if (c == EOF)
                return false;
        }
        s.clear();
        while (c != EOF && c != '\n' && c != '\r' && c != ' ' && c != '\t')
        {
            s.push_back(c);
            c = gc();
        }
        return true;
    }
} In;

struct FastPrinter
{
    static const int S = 1 << 20;
    int idx = 0;
    char buf[S];
    ~FastPrinter() { flush(); }
    inline void pc(char c)
    {
        if (idx >= S)
            flush();
        buf[idx++] = c;
    }
    inline void flush()
    {
        if (idx)
        {
            fwrite(buf, 1, idx, stdout);
            idx = 0;
        }
    }
    inline void printInt(long long x)
    {
        if (x == 0)
        {
            pc('0');
            pc('\n');
            return;
        }
        if (x < 0)
        {
            pc('-');
            x = -x;
        }
        char s[24];
        int n = 0;
        while (x)
        {
            s[n++] = char('0' + (x % 10));
            x /= 10;
        }
        while (n--)
            pc(s[n]);
        pc('\n');
    }
} Out;

// Manacher: ro[i] odd radius (#chars), re[i] even radius
static void manacher(const string &s, vector<int> &d1, vector<int> &d2)
{
    int n = (int)s.size();
    d1.assign(n, 0);
    d2.assign(n, 0);
    // odd
    for (int i = 0, l = 0, r = -1; i < n; ++i)
    {
        int k = 1;
        if (i <= r)
            k = min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k])
            ++k;
        d1[i] = k;
        if (i + k - 1 > r)
        {
            l = i - k + 1;
            r = i + k - 1;
        }
    }
    // even
    for (int i = 0, l = 0, r = -1; i < n; ++i)
    {
        int k = 0;
        if (i <= r)
            k = min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k])
            ++k;
        d2[i] = k;
        if (i + k - 1 > r)
        {
            l = i - k;
            r = i + k - 1;
        }
    }
}

struct Query
{
    int l, r, k, id;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    if (!In.readInt(n))
        return 0;
    In.readInt(q);
    string S;
    In.readString(S);
    vector<Query> qs(q);
    vector<int> ks;
    ks.reserve(q);
    for (int i = 0; i < q; ++i)
    {
        In.readInt(qs[i].l);
        In.readInt(qs[i].r);
        In.readInt(qs[i].k);
        qs[i].id = i;
        ks.push_back(qs[i].k);
    }

    vector<int> d1, d2;
    manacher(S, d1, d2);

    // group queries by k
    unordered_map<int, vector<Query>> byk;
    byk.reserve(q * 2);
    for (auto &qq : qs)
        byk[qq.k].push_back(qq);

    vector<long long> ans(q, 0);
    vector<int> MaxStart(n + 1); // 1..n, max start for pal end at e else -INF
    const int NINF = INT_MIN / 2;
    vector<int> prefMax(n + 1);
    vector<int> Next(n + 2);

    // process each k using heap sweep per parity
    for (auto &kv : byk)
    {
        int k = kv.first;
        auto &list = kv.second;
        // buckets for add events at each e
        vector<vector<pair<int, int>>> addOdd(n + 2), addEven(n + 2);
        // odd centers i in [0..n-1]: e = i + t (1-based), s = (2*(i+1)) - e
        int tmin_odd = (k + 1) / 2 + (k % 2 == 0); // ceil((k+1)/2) = (k+2)/2
        tmin_odd = (k + 2) / 2;
        for (int i = 0; i < n; ++i)
        {
            int tmax = d1[i];
            if (tmax < tmin_odd)
                continue;
            int L = i + tmin_odd;
            int R = i + tmax;
            if (L <= n)
                addOdd[L].push_back({2 * (i + 1), min(R, n)});
        }
        // even centers i in [0..n-1]: e = i + t (1-based), s = (2*i+1) - e
        int tmin_even = (k + 1) / 2; // ceil(k/2)
        for (int i = 0; i < n; ++i)
        {
            int tmax = d2[i];
            if (tmax < tmin_even)
                continue;
            int L = i + tmin_even;
            int R = i + tmax;
            if (L <= n)
                addEven[L].push_back({2 * i + 1, min(R, n)});
        }

        // sweep e=1..n maintaining heaps of (K,R) with R>=e; get best K
        struct Node
        {
            int K;
            int R;
        };
        auto cmp = [](const Node &a, const Node &b)
        { return a.K < b.K; };
        priority_queue<Node, vector<Node>, decltype(cmp)> pqOdd(cmp), pqEven(cmp);
        for (int e = 1; e <= n; ++e)
        {
            for (auto &p : addOdd[e])
                pqOdd.push({p.first, p.second});
            for (auto &p : addEven[e])
                pqEven.push({p.first, p.second});
            while (!pqOdd.empty() && pqOdd.top().R < e)
                pqOdd.pop();
            while (!pqEven.empty() && pqEven.top().R < e)
                pqEven.pop();
            int best = NINF;
            if (!pqOdd.empty())
                best = max(best, pqOdd.top().K - e);
            if (!pqEven.empty())
                best = max(best, pqEven.top().K - e);
            MaxStart[e] = best; // may be NINF if none
        }

        // prefMax[e] = max_{t<=e} MaxStart[t]
        int cur = NINF;
        for (int e = 1; e <= n; ++e)
        {
            cur = max(cur, MaxStart[e]);
            prefMax[e] = cur;
        }
        // Next[pos]: the smallest e in [pos..n] s.t. prefMax[e] >= pos; if none, Next[pos]=n+1
        int e_ptr = 1;
        for (int pos = 1; pos <= n + 1; ++pos)
        {
            while (e_ptr <= n && prefMax[e_ptr] < pos)
                ++e_ptr;
            Next[pos] = (e_ptr <= n ? e_ptr : n + 1);
        }
        // answer queries for this k via greedy interval scheduling
        for (auto &qu : list)
        {
            int l = qu.l, r = qu.r;
            int curp = l;
            int cnt = 0;
            while (curp <= r)
            {
                int e = Next[curp];
                if (e > r)
                    break;
                ++cnt;
                curp = e + 1;
            }
            ans[qu.id] = cnt;
        }
    }

    for (int i = 0; i < q; ++i)
        Out.printInt(ans[i]);
    Out.flush();
    return 0;
}