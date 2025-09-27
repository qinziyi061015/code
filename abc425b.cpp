// Problem: given N (<=10) and array a (values -1 or 1..N), fill a permutation P of 1..N respecting fixed positions.
// Approach: collect used numbers, verify no conflict (duplicate fixed values). Then place remaining numbers arbitrarily.
// Complexity: O(N log N) due to sort (N<=10 anyway).
#include <bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int N;
	cin>>N;
	vector<int> a(N);
	for (int i = 0; i < N; i++)
		cin >> a[i];
	vector<int> used(N + 1, 0); // 1..N
	for (int i = 0; i < N; i++)
		if (a[i] != -1)
		{
			if (a[i] < 1 || a[i] > N || used[a[i]])
			{
				cout << "No\n";
				return 0;
			}
			used[a[i]] = 1;
		}
	vector<int> val;
	for (int v = 1; v <= N; v++)
		if (!used[v])
			val.push_back(v);
	// fill
	int ptr = 0;
	vector<int> P(N);
	for (int i = 0; i < N; i++)
		if (a[i] == -1)
			P[i] = val[ptr++];
		else
			P[i] = a[i];
	cout << "Yes\n";
	for (int i = 0; i < N; i++)
		cout << P[i] << (i + 1 == N ? '\n' : ' ');
	return 0;
}