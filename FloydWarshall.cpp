#include <bits/stdc++.h>
using namespace std;

const int V = 1001;
int dp[V][V], v, e; // dp[i][j] najkratkiot pat od i do j

int main() {
    
    cin >> v >> e;

    for(int i = 0; i <= v; i++)
        for(int j = 0; j <= v; j++)
            dp[i][j] = (i == j) ? 0 : (1 << 28);

    while(e--) {
        int a, b, c;
        cin >> a >> b >> c;
        dp[a][b] = min(dp[a][b], c);
        dp[b][a] = min(dp[b][a], c);
    }

    for(int k = 1; k <= v; k++) 
        for(int i = 1; i <= v; i++) 
            for(int j = 1; j <= v; j++)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
        
    for(int i = 1; i <= v; i++) {
        cout << endl << "OD " << i << endl;
        for(int j = 1; j <= v; j++) 
            cout << j << " " << dp[i][j] << endl;   
    }
}