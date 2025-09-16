#include <bits/stdc++.h>
#include <atcoder/fenwicktree>
using namespace std;

int main() {
    int N, Q;
    cin >> N >> Q;

    // BIT を宣言する (N 要素が 0 で初期化される)
    atcoder::fenwick_tree<long long> bit(N);

    // 数列 a を入力として受け取り、BIT に加算していく
    for (int i = 0; i < N; ++i) {
        long long a;
        cin >> a;
        bit.add(i, a);  // i 番目に a を加算
    }

    // 各クエリ
    for (int i = 0; i < Q; ++i) {
        int type;
        cin >> type;
        if (type == 0) {
            // 加算クエリ
            long long p, x;
            cin >> p >> x;
            bit.add(p, x);
        } else {
            // 総和取得クエリ
            int l, r;
            cin >> l >> r;

            // 区間 [l, r) の総和を取得して答える
            cout << bit.sum(l, r) << endl;
        }
    }
}