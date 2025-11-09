#include <bits/stdc++.h>
using namespace std;

int n;
int main() { 
    cin >> n;
    vector<int> dp(1 << n);
    for(int &c : dp)
        cin >> c;
    for(int i = 1; i < n; i++) 
        for(int s = 0; s < (1 << n); s++) 
            if((1 << i) & s) dp[s] += dp[s^i];

    cout << dp[(1 << n) - 1];
}