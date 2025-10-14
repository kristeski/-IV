#include <bits/stdc++.h>
using namespace std;
#define int long long
const int V = 505;
const int INF = 1e18;

int cap[V][V], caps[V][V], par[V];
int v, e;
vector<int> adj[V];

int bfs(int s, int t) {
    fill(par, par + V, -1);
    par[s] = -2;
    queue<pair<int,int>> q;
    q.push({s, INF});
    while (!q.empty()) {
        auto [u, flow] = q.front();
        q.pop();
        for (int next : adj[u]) {
            if (par[next] == -1 && cap[u][next] > 0) {
                par[next] = u;
                int new_flow = min(flow, cap[u][next]);
                if (next == t) return new_flow;
                q.push({next, new_flow});
            }
        }
    }
    return 0;
}

void set_up(int v) {
    for (int i = 1; i <= v; i++)
        for (int j : adj[i])
            cap[i][j] = caps[i][j];
}

int maxflow(int s, int t) {
    int flow = 0, new_flow;
    while ((new_flow = bfs(s, t))) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = par[cur];
            cap[prev][cur] -= new_flow;
            cap[cur][prev] += new_flow;
            cur = prev;
        }
    }
    return flow;
}

int32_t main() {
    cin >> v >> e;
    while (e--) {
        int a, b, w;
        cin >> a >> b >> w;
        adj[a].push_back(b);
        adj[b].push_back(a);
        caps[a][b] = w;
        caps[b][a] = 0;
    }

    int miniMaxflow = INF;
    for (int i = 1; i <= v; i++) {
        for (auto j : adj[i]) {
            if (caps[i][j] > 0) {
                set_up(v);
                cap[i][j] = 0;
                miniMaxflow = min(miniMaxflow, maxflow(1, v));
            }
        }
    }
    cout << miniMaxflow;
}
