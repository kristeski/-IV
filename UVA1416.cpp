#include <bits/stdc++.h>
using namespace std;

// Решение со Флојд Варшалов временска комплексност O(M * V^3)

int v, m, l; 
const int N = 101;

struct Edge {
    int u, v, w;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    vector<Edge> edgelist;
    edgelist.reserve(10 * N);
    edgelist.push_back({0, 0, 1 << 29});

    cin >> v >> m >> l;

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        edgelist.push_back({a, b, w});
    }

    int maxi = 0, res, original;
    bool first = false;

    for (Edge cur : edgelist) { 
        vector<vector<int>> dp(v + 1, vector<int>(v + 1, l));
        for (int i = 1; i <= v; i++)
            dp[i][i] = 0;
        for (Edge e1 : edgelist) {
            if (cur.u == e1.u && cur.v == e1.v && cur.w == e1.w) continue;
            dp[e1.u][e1.v] = e1.w;
            dp[e1.v][e1.u] = e1.w;
        }
        res = 0;
        for (int k = 1; k <= v; k++)
            for (int i = 1; i <= v; i++)
                for (int j = 1; j <= v; j++)
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);

        for (int i = 1; i <= v; i++) {
            for (int j = 1; j <= v; j++)
                res += dp[i][j];
        }
        maxi = max(maxi, res);
        if (!first) {
            original = maxi;
            first = true;
        }
    }
    cout << original << " " << maxi;
    return 0;
}
