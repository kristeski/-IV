#include <bits/stdc++.h>
using namespace std;


int n, k;
const int N = (1 << 20);
int dp[N][40], price[20][40];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> k >> n;

    for(int i = 0; i < k; i++)
        for(int j = 0; j < n; j++)
            cin >> price[i][j];
    for(int i = 1; i < (1 << k); i++)
        for(int j = 0; j < n; j++)
            dp[i][j] = INT32_MAX >> 2;
    
    for(int i = 0; i < k; i++) 
        dp[(1 << i)][0] = price[i][0];
    for(int i = 0; i < n; i++)
        dp[0][i] = 0;

    for(int d = 1; d < n; d++) 
        for(int s = 1; s < (1 << k); s++) {
            int sum = INT32_MAX >> 2;
            for(int i = 0; i < k; i++) 
                if(s & (1 << i))
                    sum = min(sum, dp[s ^ (1 << i)][d - 1] + price[i][d]);
            dp[s][d] = min(dp[s][d - 1], sum);
        }
    cout << dp[(1 << k) - 1][n - 1];
}