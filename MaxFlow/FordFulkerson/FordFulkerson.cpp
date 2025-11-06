#include <bits/stdc++.h>
using namespace std;
const int V = 501, INF = 1e9;

int cap[V][V], p[V], v, e;
vector<int> adj[V];

int bfs(int s, int t) {
    for(int i = 0; i < V; i++)
        p[i] = -1;
    p[s] = -2;

    queue<pair<int, int>> q;
    q.push({s, INF});

    while(!q.empty()) {
        auto[u, flow] = q.front();
        q.pop();
        
        for(int nei : adj[u]) {
            if(p[nei] == -1 && cap[u][nei]) {
                p[nei] = u;
                int new_flow = min(flow, cap[u][nei]);
                if(nei == t)
                    return new_flow;
                q.push({nei, new_flow});
            }
        }
    }
    return 0;
}

void max_flow(int s, int t) {
    int MAX_FLOW = 0, flow;
    while(flow = bfs(s, t)) {
        MAX_FLOW += flow;
        int cur = t;
        stack<int> path;
        while(p[cur] != -2) {
            path.push(cur);
            cap[p[cur]][cur] -= flow;
            cap[cur][p[cur]] += flow;
            cur = p[cur];
        }
        path.push(s);

        cout << "Augmenting path: ";
        while(!path.empty()) {
            cout << path.top();
            if(path.size() > 1)
                cout << " -> ";
            path.pop();
        }
        cout << " | Flow added: " << flow << '\n';
    }
    cout << "Maximum flow = " << MAX_FLOW;
}
int main() {
    cin >> v >> e;
    while(e--) {
        int a, b, w;
        cin >> a >> b >> w;
        adj[a].push_back(b);
        adj[b].push_back(a);
        cap[a][b] += w;
    }
    max_flow(1, v);
}
