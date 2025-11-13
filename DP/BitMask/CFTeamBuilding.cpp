#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vvi vector<vector<int>>
#define vi vector<int>
#define rep(i, n) for(int i = 0; i < n; i++)
#define Rep(i, n) for(int i = 1; i <= n; i++)
#define all(x) x.begin(), x.end()
template<typename T>
istream &operator >>(istream& is, vector<T>& v) {for(T &el : v){cin >> el;} return is;}
template<typename P1, typename P2>
ostream &operator <<(ostream& os, const pair<P1, P2>& p) {return os << p.first << ' ' << p.second;}

int n, n2;


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    vi v(n);
    cin >> v;
    sort(all(v), greater<int>());

}