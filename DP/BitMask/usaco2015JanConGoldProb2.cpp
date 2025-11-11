#include <bits/stdc++.h>
using namespace std;

long long n, l;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	ofstream cout("movie.out");
	ifstream cin("movie.in");

	cin >> n >> l;
	vector<long long> len(n);
	vector<bool> res(n, false);
	vector<vector<long long>> v(n);
	for(int i = 0; i < n; i++) {
		cin >> len[i];
		int c; cin >> c;
		v[i].resize(c);
		for(int j = 0; j < c; j++) {
			cin >> v[i][j];
		}
	}
	vector<long long> dp(1 << n, -1);
	dp[0] = 0;

	for (int s = 1; s < (1 << n); s++) {
		for (int i = 0; i < n; i++) {
			if ((1 << i) & s) {
				if (dp[s ^ (1 << i)] == -1) continue;
				auto it = lower_bound(v[i].begin(), v[i].end(), dp[s ^ (1 << i)]);
				if(it != v[i].end() && *it == dp[s ^ (1 << i)]) 
					dp[s] = max(dp[s], dp[s ^ (1 << i)] + len[i]);
				else if (it != v[i].end() && it != v[i].begin()) {
					it--;
					dp[s] = max(dp[s], *it + len[i]);
				}
			}
		}
		if (dp[s] >= l) 
			res[__builtin_popcount(s)] = true;
	}

	for (int i = 0; i < n; i++) {
		if (res[i]) {
			cout << i;
			return 0;
		}
	}
	cout << -1;

}