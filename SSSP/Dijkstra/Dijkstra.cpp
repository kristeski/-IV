#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 1, inf = INT32_MAX >> 1;
vector<pair<int, int>> adj[N];
int distances_to[N], n, m;

void init(){ 
    for(int i = 0; i < N; i++) {
        distances_to[i] = inf;
    }
}

void dijkstra (int start_node){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    distances_to[start_node] = 0;
    pq.push({0, start_node});

    while(!pq.empty()) {
        auto [distance, node] = pq.top();
        pq.pop();
        
        if(distance > distances_to[node]) 
            continue;
            
        for(auto [neibour, weight] : adj[node]) {
            if(distances_to[neibour] > distance + weight) {
                distances_to[neibour] = distance + weight;
                pq.push({distances_to[neibour], neibour});
            }
        }
    }

}
int main() {
    cin >> n >> m;
    int node1, node2, dist;
    while(m--) {
        cin >> node1 >> node2 >> dist;
        adj[node1].push_back({node2, dist});
        adj[node2].push_back({node1, dist});
    }
    init();
    dijkstra(1);
}