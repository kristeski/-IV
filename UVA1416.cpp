#include <bits/stdc++.h>
using namespace std;

// Решение со Флојд Варшалов временска комплексност O(M * V^3)
#define int long long
int v, m, l; 
const int N = 101, inf = 1 << 29;

struct Edge {
    int u, v, w;
};
int floyd(const vector<Edge> &vec, const Edge ed) {
    int res = 0;
    vector<vector<int>> dp(v + 1, vector<int>(v + 1, inf));
    for(int i = 1; i <= v; i++)
        dp[i][i] = 0;
    for(Edge e: vec) {
        if(e.u == ed.u && e.v == ed.v && e.w == ed.w) 
            continue;
        dp[e.u][e.v] = e.w;
        dp[e.v][e.u] = e.w;
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
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    vector<Edge> edgelist;
    edgelist.reserve(10 * N);

    cin >> v >> m >> l;

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        edgelist.push_back({a, b, w});
    }

    int maxi = 0, res, original = 0;
    original = floyd(edgelist, {0, 0, 0});

    for(Edge e : edgelist) 
        maxi = max(maxi, floyd(edgelist, e));
    
    cout << original << " " << maxi;
    return 0;
}
