#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w; 
};

const int inf = 1 << 29;

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    vector<int> dist(n + 1, inf);
    dist[0] = 0;

    for (int i = 1; i < n; i++) {
        for (auto e : edges) {
            if (dist[e.u] != inf && dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
            }
        }
    }

    bool hasNegativeCycle = false;
    for (auto e : edges) {
        if (dist[e.u] != inf && dist[e.u] + e.w < dist[e.v]) {
            hasNegativeCycle = true;
            break;
        }
    }

    if (hasNegativeCycle) {
        cout << "Grafot sodrzi negativni ciklusi\n";
    } else {
        for (int i = 1; i <= n; i++) {
            if (dist[i] == inf) cout << " nedostapno ";
            else cout << dist[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
