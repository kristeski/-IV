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

bool custcomparator(const edge &e1, const edge &e2) {
    return tie(e1.fr, e1.to, e1.wei) < tie(e2.fr, e2.to, e2.wei);
}

int main() {
    random_device rd;
    mt19937 rng(rd());

    uniform_int_distribution<int> nodeDist(2, 50);
    int nodes = nodeDist(rng);

    uniform_int_distribution<int> extraEdges(0, nodes - 1);
    int edges = 2 * (nodes - 1) + extraEdges(rng);

    uniform_int_distribution<int> randomNode(1, nodes);
    uniform_int_distribution<int> randomWeight(-20, 50);

    dsu.assign(nodes + 1, -1);

    for (int i = 2; i <= nodes; i++) {
        int ran = randomNode(rng);
        while (findp(ran) == findp(i)) {
            ran = randomNode(rng);
        }
        int wei = randomWeight(rng);
        edgelist.push_back({i, ran, abs(wei)});
        edgelist.push_back({ran, i, abs(wei)});
        uni(i, ran);
    }

    edges -= 2 * (nodes - 1);
    while (edges--) {
        int a = randomNode(rng), b = randomNode(rng);
        if (a == b) {
            edges++; 
            continue;
        }
        int wei = randomWeight(rng);
        edgelist.push_back({a, b, wei});
    }

    ofstream foutGraph("RandomGenGraph.txt", ios::app);
    foutGraph << "\n\n\n------- NEW GRAPH -------\n";
    foutGraph << "Teminja: " << nodes << "\nRebra: " << edgelist.size() << "\n";
    foutGraph << "--Teme1--  --Teme2--  --Tezina--\n"; 

    sort(edgelist.begin(), edgelist.end(), custcomparator);
    for(auto e : edgelist) 
        foutGraph << "   " << e.fr << "        " << e.to << "         " << e.wei << '\n';
            
    
    const int INF = 1 << 29;
    vector<int> dist(nodes + 1, INF);
    dist[1] = 0;

    for (int i = 1; i <= nodes - 1; i++) {
        bool updated = false;
        for (auto &e : edgelist) {
            if (dist[e.fr] != INF && dist[e.fr] + e.wei < dist[e.to]) {
                dist[e.to] = dist[e.fr] + e.wei;
                updated = true;
            }
        }
        if (!updated) break;
    }

    bool negCycle = false;
    for (auto &e : edgelist) {
        if (dist[e.fr] != INF && dist[e.fr] + e.wei < dist[e.to]) {
            negCycle = true;
            break;
        }
    }
    ofstream foutResult("Result.txt", ios::app);
    foutResult << "\n\n\n------- NEW GRAPH -------\n";
    if (negCycle) {
        foutResult << "Detektiran negativen ciklus!\n";
    } else {
        foutResult << "Najkratok pat do teminja od pocetno teme 1:\n";
        for (int i = 1; i <= nodes; i++) {
            if (dist[i] == INF)
                foutResult << "do " << i << ": nedostapno\n";
            else
                foutResult << "do " << i << ": " << dist[i] << "\n";
        }
    }

    foutResult << "\n";
    return 0;
}
