#include <bits/stdc++.h>
using namespace std;

struct FastScanner
{
    static const int S = 1 << 20; // 1MB
    int idx = 0, size = 0;
    char buf[S];
    inline char getcFast()
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
    template <class T>
    bool readInt(T &out)
    {
        char c;
        T sign = 1, x = 0;
        c = getcFast();
        if (c == EOF)
            return false;
        while (c != '-' && (c < '0' || c > '9'))
        {
            c = getcFast();
            if (c == EOF)
                return false;
        }
        if (c == '-')
        {
            sign = -1;
            c = getcFast();
        }
        for (; c >= '0' && c <= '9'; c = getcFast())
            x = x * 10 + (c - '0');
        out = x * sign;
        return true;
    }
} In;

struct FastPrinter
{
    static const int S = 1 << 20;
    int idx = 0;
    char buf[S];
    ~FastPrinter() { flush(); }
    inline void pushChar(char c)
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
    template <class T>
    inline void printInt(T x)
    {
        if (x == 0)
        {
            pushChar('0');
            return;
        }
        if (x < 0)
        {
            pushChar('-');
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
            pushChar(s[n]);
    }
} Out;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!In.readInt(T))
        return 0;
    while (T--)
    {
        int n;
        long long m;
        In.readInt(n);
        In.readInt(m);
        vector<int> a(n);
        for (int i = 0; i < n; ++i)
            In.readInt(a[i]);

        int N2 = 2 * n;
        vector<int> b(N2);
        for (int i = 0; i < n; ++i)
            b[i] = b[i + n] = a[i];

        vector<int> r(N2);
        deque<int> qmax, qmin; 
        int rr = -1;
        for (int i = 0; i < N2; ++i)
        {
            int limit = min(N2 - 1, i + n - 1);
            while (rr + 1 <= limit)
            {
                int nr = rr + 1;
                while (!qmax.empty() && b[qmax.back()] < b[nr])
                    qmax.pop_back();
                qmax.push_back(nr);
                while (!qmin.empty() && b[qmin.back()] > b[nr])
                    qmin.pop_back();
                qmin.push_back(nr);
                if ((long long)b[qmax.front()] - (long long)b[qmin.front()] <= m)
                    rr = nr;
                else
                {
                    if (!qmax.empty() && qmax.back() == nr)
                        qmax.pop_back();
                    if (!qmin.empty() && qmin.back() == nr)
                        qmin.pop_back();
                    break;
                }
            }
            r[i] = rr;
            if (!qmax.empty() && qmax.front() == i)
                qmax.pop_front();
            if (!qmin.empty() && qmin.front() == i)
                qmin.pop_front();
        }

        int SENT = N2; 
        vector<int> nextIdx(N2 + 1, SENT);
        for (int i = 0; i < N2; ++i)
            nextIdx[i] = min(r[i] + 1, SENT);
        nextIdx[SENT] = SENT;

        int K = 1;
        while ((1 << K) <= n)
            ++K; 
        vector<int> up(K * (N2 + 1), SENT);
        auto U = [&](int k, int i) -> int &
        { return up[k * (N2 + 1) + i]; };
        for (int i = 0; i <= N2; ++i)
            U(0, i) = nextIdx[i];
        for (int k = 1; k < K; ++k)
        {
            for (int i = 0; i <= N2; ++i)
            {
                int mid = U(k - 1, i);
                U(k, i) = U(k - 1, mid);
            }
        }

        int best = INT_MAX;
        for (int s = 0; s < n; ++s)
        {
            int target = s + n;
            int pos = s;
            int cnt = 0;
            for (int k = K - 1; k >= 0; --k)
            {
                int np = U(k, pos);
                if (np < target)
                {
                    pos = np;
                    cnt += (1 << k);
                }
            }
            ++cnt; 
            if (cnt < best)
                best = cnt;
        }

        Out.printInt(best);
        Out.pushChar('\n');
    }
    Out.flush();
    return 0;
}