#include <iostream>
#include <iomanip>
#include <queue>

int main() {
    using namespace std;
    cout << setprecision(15);
    unsigned T;
    cin >> T;
    for (unsigned t{}; t < T; ++t) []{
        unsigned N, K, X;
        cin >> N >> K >> X;
        // (長さ, 本数) を管理する priority_queue
        priority_queue<pair<double, unsigned>> pq;
        for (unsigned i{}; i < N; ++i) {
            double a;
            cin >> a;
            pq.emplace(a, 1); // はじめ、長さ a が 1 本ある（重複があっても気にしない）
        }

        // 操作を行う
        while (K) {
            const auto [a, count]{pq.top()};
            pq.pop();
            if (K <= count) { // ここで終わりなら
                pq.emplace(a / 2, K * 2); // 途中まで操作して
                pq.emplace(a, count - K); // いくつか残る
                K = 0;
                break;
            } // そうでなければ
            pq.emplace(a / 2, count * 2); // 全部半分になる
            K -= count;
        }

        // 大きいほうから X 番目を求める
        while (X) {
            const auto [a, count]{pq.top()};
            pq.pop();
            if (X <= count) {
                cout << a << '\n';
                break;
            }
            X -= count;
        }
    }();
    return 0;
}

