
// AtCoder ABC 424 D: 2 x 2 Erasing 2

// 题意（简述）：
// 给定 H x W 的网格，部分格子为黑色（'#'）。你可以把任意黑格子擦掉（变成 '.'），
// 代价是擦掉的黑格子总数。要求最终棋盘中不存在任何 2x2 的全黑子矩形，求最小代价。

// 做法（状态压缩 DP）：
// - 每一行用一个长度为 W 的 bitmask 表示保留的黑格子子集（1 表示该列保留黑格子）。
// - 设 orig[i] 为第 i 行原始黑格子的掩码，blacks[i] 为该行黑格子数量。
// - 若选择当前行掩码 m，则必须满足 m 是 orig[i] 的子集：m & ~orig[i] == 0（只能擦，不能凭空添黑）。
// - 两行相邻（上一行 pm，本行 m）时，禁止出现 2x2 全黑：
//   若同列交集 x = (pm & m) 在相邻两列出现连续两位 1（即 (x & (x << 1)) != 0），
//   则在这两行、这两列构成一个 2x2 全黑块，不合法。于是合法性条件为 (x & (x << 1)) == 0。
// - 代价：当前行从 blacks[i] 个黑格中保留 fx(m) 个，擦掉 blacks[i] - fx(m)。
// - dp[i][m]：处理到第 i 行，且第 i 行保留子集为 m 的最小代价。用一维滚动数组 dp[m] 表示上一行结果。
// - 预处理 ok[pm][m] 表示相邻两行的掩码是否可相邻（不形成 2x2 全黑）。

// 复杂度：
// - 预处理 ok 复杂度 O(4^W)（即 O(2^{2W})）。
// - DP 转移 O(H * 4^W)。适用于 W 较小（如 W ≤ 10）的情况。

// 实现细节：
// - 使用 __builtin_popcount 统计掩码中的 1 的个数。
// - 为避免类型问题，对 popcount 传入 unsigned 进行计算。

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
		int M = 1 << W;                 // 每一行掩码的状态空间大小
		vector<int> orig(H, 0),blacks(H, 0);
		for (int i = 0; i < H; ++i) {
			int mask = 0, b = 0;
			for (int j = 0; j < W; ++j) if (S[i][j] == '#') { mask |= (1 << j); ++b; }
			orig[i] = mask; blacks[i] = b; // 记录该行原始黑格掩码与黑格数量
		}
		// 预处理相邻两行掩码是否“不会形成 2x2 全黑”
		vector<vector<char>> ok(M, vector<char>(M, 0));
		for (int a = 0; a < M; ++a) {
			for (int b = 0; b < M; ++b) {
				int x = a & b; // 两行同一列都为 1 的位置集合
				// 若 x 存在相邻两位都为 1，即 (x & (x << 1)) != 0，则出现 2x2 全黑，不合法
				ok[a][b] = ((x & (x << 1)) == 0);
			}
		}
		vector<int> dp(M, INF), tmp(M, INF);
		// 初始化第 0 行：选择任意 m ⊆ orig[0]
		for (int m = 0; m < M; ++m) if ((m & ~orig[0]) == 0) {
			dp[m] = blacks[0] - fx((unsigned)m); // 擦掉数量 = 原黑数 - 保留数
		}
		for (int i = 1; i < H; ++i) {
			fill(tmp.begin(), tmp.end(), INF);
			for (int pm = 0; pm < M; ++pm) if (dp[pm] < INF) { // 枚举上一行掩码 pm
				for (int m = 0; m < M; ++m) {
					if ((m & ~orig[i]) != 0) continue; // 必须为原始黑格的子集
					if (!ok[pm][m]) continue;          // 相邻两行不能形成 2x2 全黑
					int cost = blacks[i] - fx((unsigned)m);
					tmp[m] = min(tmp[m], dp[pm] + cost);
				}
			}
			dp = tmp; // 滚动数组更新
		}
		int ans = INF;
		for (int m = 0; m < M; ++m) ans = min(ans, dp[m]); // 取最后一行的最小代价
		cout << ans << '\n';
	}
	return 0;
}