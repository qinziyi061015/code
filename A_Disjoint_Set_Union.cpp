#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;

int main() {
    int N, Q;
    cin >> N >> Q;

    // サイズ N の Union-Find を宣言
    atcoder::dsu uf(N);

    // クエリ処理
    for (int i = 0; i < Q; ++i) {
        int type, u, v;
        cin >> type >> u >> v;
        if (type == 1) 
            cout << (uf.same(u, v) ? 1 : 0) << endl;
        else
            uf.merge(u, v);
    }
}