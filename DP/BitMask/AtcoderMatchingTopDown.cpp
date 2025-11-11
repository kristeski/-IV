#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> a;
int n;
const int M = 1e9 + 7;;
vector<int> compat, dp;

int rec(int mask) {
	if(mask == (1 << n) - 1)
		return 1;
	if(dp[mask] != -1)
		return dp[mask];
	int &res = dp[mask];
	res = 0;
	int man = __builtin_popcount(mask);
	int zen = (~mask) & compat[man];
	while(zen) {
		int bit = zen & -zen;
		zen ^= bit;
		res = (res + rec(mask|bit)) % M;
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin >> n;
	compat.resize(n); dp.assign((1 << n), -1);
	a.resize(n, vector<int>(n, 0));
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++) {
			cin >> a[i][j];
			if(a[i][j]) 
				compat[i] |= (1 << j);
		}
	
	rec(0);
	cout << dp[0];
}