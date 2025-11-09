#include <bits/stdc++.h>
using namespace std;


int n, m;
const int N = (1 << 20), M = 1e9 + 7;
int dp[N][20];
vector<int> adj[20];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> n >> m;
    while(m--) {
        int a, b;
        cin >> a >> b;
        adj[--b].push_back(--a);
    }
    dp[1][0] = 1;
    for(int s = 3; s < N; s += 2)
        for(int i = 1; i < n; i++)
            if((1 << i) & s)
                for(int j : adj[i])
                        dp[s][i] = (dp[s ^ (1 << i)][j] + dp[s][i]) % M;
    cout << dp[(1 << n) - 1][n - 1];
}