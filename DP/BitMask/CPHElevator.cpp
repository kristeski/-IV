#include <bits/stdc++.h>
using namespace std;

int x, n;
int main() { 
    cin >> x >> n;
    vector<pair<int, int>> dp(1 << n, {n + 1, 0});
    vector<int> wei(n);
    for(int &i : wei)
        cin >> i;

    dp[0] = {1, 0};
    for(int s = 0; s < (1 << n); s++) {
        int pomi, pomi1;
        for(int i = 0; i < n; i++) 
            if((1 << i) & s) {
                pomi = dp[s ^ (1 << i)].first;
                pomi1 = dp[s^(1 << i)].second + wei[i];
                if(pomi1 > x) {
                    pomi1 = wei[i];
                    pomi++;
                }
                dp[s] = min(dp[s], {pomi, pomi1});
            }  
    }
    cout << dp[(1 << n) - 1].first;
}