#include <bits/stdc++.h>
#define int long long
using namespace std;
int n;
string s;
int solve(char c)
{

	vector<int> pos;
	for (int i = 0; i < n; i++)
		if (s[i] == c)
			pos.push_back(i);
	int len = pos.size();
	if (len <= 1)
		return 0; 
	vector<int> b;
	for (int i = 0; i < len; i++)
		b.push_back(pos[i] - i);
	nth_element(b.begin(), b.begin() + len / 2, b.end());
	int cost = 0;
	for (int i = 0; i < len; i++)
		cost += llabs(pos[i] - (b[len / 2] + i));
	return cost;
};
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--)
	{
		cin >> n >> s;
		int ans = min(solve('a'), solve('b'));
		cout << ans << "\n";
	}
	return 0;
}