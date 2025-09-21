#include <bits/stdc++.h>
using namespace std;

// Решение со Флојд Варшалов временска комплексност O(M * V^3)
#define ll long long
ll v, m, l; 
const ll N = 101, inf = 1e18;

struct Edge {
    ll u, v, w;
};

ll floyd(const vector<Edge> &vec, ll ban) {
    ll res = 0;
    vector<vector<ll>> dp(v + 1, vector<ll>(v + 1, inf));
    for(int i = 1; i <= v; i++)
        dp[i][i] = 0;
    for(int i = 0; i < vec.size(); i++) {
        if(i == ban) continue;
        auto [a, b, w] = vec[i];
        dp[a][b] = min(dp[a][b], w);
        dp[b][a] = min(dp[b][a], w);
    }

    for(int k = 1; k <= v; k++) 
        for(int i = 1; i <= v; i++)
            for(int j = 1; j <= v; j++)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
        
    for(int i = 1; i <= v; i++)
        for(int j = 1; j <= v; j++)
            res += (dp[i][j] < inf) ? dp[i][j] : l;
    return res;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    while(cin >> v >> m >> l) {
        vector<Edge> edgelist;
        edgelist.reserve(10 * N);

        while(m--){ 
            ll a, b, w;
            cin >> a >> b >> w;
            edgelist.push_back({a, b, w});
        }

        ll original = floyd(edgelist, -1);
        ll maxi = 0;

        for(int i = 0; i < edgelist.size(); i++)
            maxi = max(maxi, floyd(edgelist, i));
        
        cout << original << " " << maxi << "\n";
    }
    return 0;
}
