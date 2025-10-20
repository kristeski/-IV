#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;

struct Edge {
    int to, rev, cap;
};
struct Dinic {
    int n, s, t;
    vector<vector<Edge>> g;
    vector<int> lvl, ptr;

    Dinic(int n, int s, int t) : n(n), s(s), t(t), g(n), lvl(n), ptr(n) {}
    
    void addEdge(int u, int v, int c) {
        g[u].push_back({v, c, (int)g[v].size()});
        g[v].push_back({u, 0, (int)g[u].size() - 1});
    }
    
    bool bfs(){ 
        fill(lvl.begin(), lvl.end(), -1);
        queue<int> q;
        q.push(s); lvl[s] = 0;
        while(!q.empty()) {
            int v = q.front(); q.pop();
            for(auto &e : g[v]) {
                if(e.cap > 0 && lvl[e.to] == -1) {
                    lvl[e.to] = lvl[v] + 1;
                    q.push(e.to);
                }
            }
        }
        return lvl[t] != -1;
    }
    int dfs(int v, int pushed) {
        if(!pushed || v == t)
            return pushed;
        for(int &cid = ptr[v]; cid < g[v].size(); cid++) {
            Edge &e = g[v][cid];
            if(e.cap > 0 && lvl[e.to] == lvl[v] + 1) {
                int tr = dfs(e.to, min(pushed, e.cap));
                if(tr) {
                    e.cap -= tr;
                    g[e.to][e.rev].cap += tr;
                    return tr;
                }
            }
        }
        return 0;
    }
    int maxflow(){ 
        int flow = 0;
        while(bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while(int pushed = dfs(s, INF))
                flow += pushed;
        }
        return flow;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    int s, t;
    cin >> s >> t;
    Dinic D(n, s, t);

    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        D.addEdge(u, v, w);
    }
    cout << D.maxflow() << '\n';
}