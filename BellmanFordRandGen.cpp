#include <bits/stdc++.h>
#include <random>
using namespace std;

struct edge {
    int fr, to, wei;
};
vector<edge> edgelist;
vector<int> dsu;

int findp(int a) {
    if (dsu[a] < 0) return a;
    return dsu[a] = findp(dsu[a]);
}

void uni(int a, int b) {
    a = findp(a);
    b = findp(b);
    if (a == b) return;
    if (dsu[a] > dsu[b]) swap(a, b);
    dsu[a] += dsu[b];
    dsu[b] = a;
}

int main() {
    random_device rd;
    mt19937 rng(rd());

    uniform_int_distribution<int> nodeDist(2, 60);
    int nodes = nodeDist(rng);

    uniform_int_distribution<int> extraEdges(0, nodes - 1);
    int edges = nodes + extraEdges(rng);

    uniform_int_distribution<int> randomNode(1, nodes);
    uniform_int_distribution<int> randomWeight(-25, 50);

    dsu.resize(nodes + 1, -1);
    set<pair<int,int>> used;

    for (int i = 2; i <= nodes; i++) {
        int ran = randomNode(rng);
        while (findp(ran) == findp(i)) {
            ran = randomNode(rng);
        }
        int wei = randomWeight(rng);
        edgelist.push_back({i, ran, wei});
        edgelist.push_back({ran, i, wei});
        used.insert({min(i, ran), max(i, ran)});
        uni(i, ran);
    }

    edges -= (nodes - 1);
    while (edges--) {
        int a = randomNode(rng);
        int b = randomNode(rng);

        if (a == b) { 
            edges++; 
            continue; 
        }
        
        if (used.count({min(a, b), max(a, b)})) { 
            edges++;
            continue; 
        }

        int wei = randomWeight(rng);
        edgelist.push_back({a, b, wei});
        edgelist.push_back({b, a, wei});
        used.insert({min(a, b), max(a, b)});
    }

    ofstream foutGraph("graph.txt");
    foutGraph << nodes << " " << used.size() << "\n"; 
    for (auto &p : used) {
        for (auto &e : edgelist) {
            if ((min(e.fr, e.to) == p.first) && (max(e.fr, e.to) == p.second)) {
                foutGraph << "Rebro pomegju: " << p.first << " i " << p.second << " so dolzina: " << e.wei << '\n';
                break;
            }
        }
    }


    const int INF = 1 << 29;
    vector<int> dist(nodes + 1, INF);
    dist[1] = 0;

    for (int i = 1; i <= nodes - 1; i++) {
        for (auto &e : edgelist) {
            if (dist[e.fr] != INF && dist[e.fr] + e.wei < dist[e.to]) {
                dist[e.to] = dist[e.fr] + e.wei;
            }
        }
    }

    bool negCycle = false;
    for (auto &e : edgelist) {
        if (dist[e.fr] != INF && dist[e.fr] + e.wei < dist[e.to]) {
            negCycle = true;
            break;
        }
    }

    ofstream foutResult("result.txt");
    if (negCycle) {
        foutResult << "Detektiran negativen ciklus\n";
    } else {
        foutResult << "Najkratok pat do teminja od pocetno teme 1:\n";
        for (int i = 1; i <= nodes; i++) {
            if (dist[i] >= INF/2)
                foutResult << "do " << i << ": nedostapno\n";
            else
                foutResult << "do " << i << ": " << dist[i] << "\n";
        }
    }

    return 0;
}
