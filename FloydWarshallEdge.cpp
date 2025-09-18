#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

const int N = 1001, inf = (1 << 29);
vector<tuple<int, int, int>> edgel, invedgel;
unordered_map<int, int> used;
int v, e;

bool custsort(const tuple<int, int, int> &t1, const tuple<int, int, int> &t2) {
    return tie(get<0>(t1), get<1>(t1), get<2>(t1)) < tie(get<0>(t2), get<1>(t2), get<2>(t2));
}
int kluc(int i, int j) {
    return (v * (i - 1) + j);
}
pair<int, int> getr(const vector<tuple<int, int, int>> &v, int num) {
    int l = lower_bound(v.begin(), v.end(), make_tuple(num, INT32_MIN, INT32_MIN)) - v.begin();
    int r = upper_bound(v.begin(), v.end(), make_tuple(num, INT32_MAX, INT32_MAX)) - v.begin();
    return {l, r};
}
void update(int indx1, int indx2) { //indx1 - prevrteno indx2 originalno
    int node1 = get<1>(invedgel[indx1]);
    int node2 = get<1>(edgel[indx2]);
    int weight = get<2>(edgel[indx2]);
    weight += get<2>(edgel[used[kluc(get<1>(invedgel[indx1]), get<0>(invedgel[indx1]))]]);
    int indx = kluc(node1, node2);
    get<2>(edgel[indx]) = min(get<2>(edgel[indx]), weight);
}
int main() {
    cin >> v >> e;
    while(e--) {
        int a, b , w;
        cin >> a >> b >> w;
        edgel.push_back({a, b, w});
        invedgel.push_back({b, a, w});
        used[kluc(a, b)] = 1;
    }

    for(int i = 1; i <= v; i++) {
        for(int j = 1; j <= v; j++) {
            if(!used[kluc(i, j)]) {
                used[kluc(i, j)] = 1;
                if(i == j) {
                    edgel.push_back({i, j, 0});
                    invedgel.push_back({j, i, 0});
                    continue; //p
                }
                edgel.push_back({i, j, inf});
                invedgel.push_back({j, i, inf});
            }
        }
    }

    sort(edgel.begin(), edgel.end(), custsort);
    sort(invedgel.begin(), invedgel.end(), custsort);

    for(int i = 0; i < edgel.size(); i++) {
        used[kluc(get<0>(edgel[i]), get<1>(edgel[i]))] = i;
    }

    for(int k = 1; k <= v; k++) {
        pair<int, int> p1 = getr(edgel, k), p2 = getr(invedgel, k);
        for(int i = p2.first; i <= p2.second; i++) 
            for(int j = p1.first; j <= p1.second; j++) 
                update(i, j);
        for(auto i : edgel) 
            cout << "Дистанца од теме " << get<0>(i) << " до " << get<1>(i) << " е: " << get<2>(i) << '\n';
    }
    
    return 0;
}