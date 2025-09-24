#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; 
    cin>>n;
    vector<int> A(n + 1), B(n + 1);
    vector<vector<int>> e(n + 1);
    vector<char> vis(n + 1, 0);
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        int a, b; 
        cin >> a >> b;
        A[i] = a; B[i] = b;
    }
    for (int i = 1; i <= n; ++i) {
        int a = A[i], b = B[i];
        if (a == 0 && b == 0) {
            if (!vis[i]) { vis[i] = 1; q.push(i); }
        } else {
            e[a].push_back(i);
            e[b].push_back(i);
        }
    }
    int ans = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ++ans;
        for (int v : e[u]) if (!vis[v]) {
            vis[v] = 1; q.push(v);
        }
    }
    cout << ans << '\n';
    return 0;
}