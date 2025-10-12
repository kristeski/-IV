#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge {
    int to;         
    int rev;        
    ll cap;         
    Edge(int _to, int _rev, ll _cap) : to(_to), rev(_rev), cap(_cap) {}
};

struct MaxFlow {
    int n;
    vector<vector<Edge>> g;
    vector<char> seen;         
    MaxFlow(int n) : n(n), g(n), seen(n) {}

    void addEdge(int u, int v, ll c) {
        g[u].emplace_back(v, (int)g[v].size(), c);
        g[v].emplace_back(u, (int)g[u].size() - 1, 0); 
    }

    ll dfs(int u, int t, ll f, vector<int>& path) {
        if (u == t) {
            path.push_back(u);
            return f;
        }
        seen[u] = 1;
        path.push_back(u);
        for (auto& e : g[u]) {
            if (!seen[e.to] && e.cap > 0) {
                ll pushed = dfs(e.to, t, min(f, e.cap), path);
                if (pushed > 0) {
                    e.cap -= pushed;
                    g[e.to][e.rev].cap += pushed;
                    return pushed;
                }
            }
        }
        path.pop_back();
        return 0;
    }

    ll maxFlow(int s, int t) {
        ll flow = 0;
        while (true) {
            fill(seen.begin(), seen.end(), 0);
            vector<int> path;
            ll pushed = dfs(s, t, LLONG_MAX, path);
            if (pushed == 0) break;
            cout << "Augmenting path (flow = " << pushed << "): ";
            for (size_t i = 0; i < path.size(); ++i) {
                if (i) cout << " -> ";
                cout << path[i];
            }
            cout << "\n";
            flow += pushed;
        }
        return flow;
    }

    void printResidual() {
        cout << "Residual graph:\n";
        for (int u = 0; u < n; ++u) {
            for (auto& e : g[u]) {
                if (e.cap > 0)
                    cout << "  " << u << " -> " << e.to << " : cap = " << e.cap << "\n";
            }
        }
    }
};

int main() {
    int N = 6;
    MaxFlow mf(N);
    mf.addEdge(0, 1, 7);
    mf.addEdge(0, 2, 4);
    mf.addEdge(2, 1, 3);
    mf.addEdge(1, 3, 5);
    mf.addEdge(1, 4, 3);
    mf.addEdge(2, 4, 2);
    mf.addEdge(3, 5, 8);
    mf.addEdge(4, 5, 5);

    int s = 0, t = 5;
    cout << "Computing max flow from " << s << " to " << t << "...\n\n";
    ll maxflow = mf.maxFlow(s, t);
    cout << "\nMax flow = " << maxflow << "\n\n";
    mf.printResidual();
    return 0;
}
