#include <bits/stdc++.h>
using namespace std;

const int V = 1001, inf = (1 << 29);
int dp[V][V], v, e; // dp[i][j] најкраток пат од i до j

int main() {
    
    cin >> v >> e;

    for(int i = 0; i <= v; i++)
        for(int j = 0; j <= v; j++)
            dp[i][j] = (i == j) ? 0 : inf;

    while(e--) {
        int a, b, c;
        cin >> a >> b >> c;
        dp[a][b] = min(dp[a][b], c);
        dp[b][a] = min(dp[b][a], c);
    }

    for(int k = 1; k <= v; k++) {
        cout << "Состојба со прв/ите " << k << " можни посредни темиња\n";
        for(int i = 1; i <= v; i++) {
            cout << "Дистанца од теме број " << i << " до останатите\n";
            for(int j = 1; j <= v; j++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
                cout << ((dp[i][j] == inf) ? (char)236 : dp[i][j]) << " ";
            }
            cout << endl;
        }
    }
        
}