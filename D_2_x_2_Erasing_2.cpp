#include <bits/stdc++.h>
using namespace std;
#define fx __builtin_popcount
const int INF = 1e9;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T; 
	cin>>T;
	while (T--) {
		int H, W; 
		cin >> H >> W;
		vector<string> S(H);
		for (int i = 0; i < H; ++i) cin >> S[i];
		int M = 1 << W;
		vector<int> orig(H, 0),blacks(H, 0);
		for (int i = 0; i < H; ++i) {
			int mask = 0, b = 0;
			for (int j = 0; j < W; ++j) if (S[i][j] == '#') { mask |= (1 << j); ++b; }
			orig[i] = mask; blacks[i] = b;
		}
		vector<vector<char>> ok(M, vector<char>(M, 0));
		for (int a = 0; a < M; ++a) {
			for (int b = 0; b < M; ++b) {
				int x = a & b;
				ok[a][b] = ((x & (x << 1)) == 0);
			}
		}
		vector<int> dp(M, INF), tmp(M, INF);
		for (int m = 0; m < M; ++m) if ((m & ~orig[0]) == 0) {
			dp[m] = blacks[0] - fx((unsigned)m);
		}
		for (int i = 1; i < H; ++i) {
			fill(tmp.begin(), tmp.end(), INF);
			for (int pm = 0; pm < M; ++pm) if (dp[pm] < INF) {
				for (int m = 0; m < M; ++m) {
					if ((m & ~orig[i]) != 0) continue; 
					if (!ok[pm][m]) continue; 
					int cost = blacks[i] - fx((unsigned)m);
					tmp[m] = min(tmp[m], dp[pm] + cost);
				}
			}
			dp=tmp;
		}
		int ans = INF;
		for (int m = 0; m < M; ++m) ans = min(ans, dp[m]);
		cout << ans << '\n';
	}
	return 0;
}