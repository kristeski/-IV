#include <bits/stdc++.h>
using namespace std;

const int M = 1e9+7;
const int N = 1 << 20;
int n, m;
vector<int> adj[20];
int dp[N][20];    // [mask][i] kaj zavrsuvaat

int main(){ 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m; 

    while(m--) {
        int a, b;
        cin >> a >> b;
        adj[--b].push_back(--a);
    }

    dp[1][0] = 1;
    for(int mask = 3; mask < N; mask+=2) {
        for(int i = 1; i < 20; i++) {
            if((1 << i) & mask) {
                for(int j : adj[i]) {
                    if((1 << j) & mask)
                        dp[mask][i] = (dp[mask - (1 << i)][j] + dp[mask][i]) % M;
                }
            }
        }
    }
    int sum = 0;
    for(int i = 1; i < 20; i++) 
        sum = (sum + dp[(1 << n) - 1][i]) % M;
    cout << sum;
}