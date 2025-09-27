
#include <bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int H, W;
	cin>>H>>W;
	vector<string> S(H);
	for (int i = 0; i < H; i++)
		cin >> S[i];
	const int dx[4] = {1, -1, 0, 0};
	const int dy[4] = {0, 0, 1, -1};
	vector<vector<int>> deg(H, vector<int>(W, 0));
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			if (S[i][j] == '#')
			{
				for (int d = 0; d < 4; d++)
				{
					int ni = i + dx[d], nj = j + dy[d];
					if (ni < 0 || ni >= H || nj < 0 || nj >= W)
						continue;
					deg[ni][nj]++;
				}
			}
	vector<pair<int, int>> cur;
	vector<pair<int, int>> c;
	vector<vector<char>> inc(H, vector<char>(W, 0));
	// initial round: scan all
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			if (S[i][j] == '.' && deg[i][j] == 1)
				cur.push_back({i, j});
	while (!cur.empty())
	{
		// color all in cur
		c.clear();
		for (auto &p : cur)
		{
			int x = p.first, y = p.second;
			S[x][y] = '#';
		}
		// update neighbors, collect c white neighbors
		for (auto &p : cur)
		{
			int x = p.first, y = p.second;
			for (int d = 0; d < 4; d++)
			{
				int nx = x + dx[d], ny = y + dy[d];
				if (nx < 0 || nx >= H || ny < 0 || ny >= W)
					continue;
				if (S[nx][ny] == '.')
				{
					deg[nx][ny]++;
					if (!inc[nx][ny])
					{
						inc[nx][ny] = 1;
						c.push_back({nx, ny});
					}
				}
			}
		}
		// build nxt cur from c set where now (after updates) deg==1
		vector<pair<int, int>> nxt;
		for (auto &p : c)
		{
			int x = p.first, y = p.second;
			inc[x][y] = 0;
			if (S[x][y] == '.' && deg[x][y] == 1)
				nxt.push_back(p);
		}
		cur.swap(nxt);
	}
	long long ans = 0;
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			if (S[i][j] == '#')
				ans++;
	cout << ans << "\n";
	return 0;
}
