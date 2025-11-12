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
ll dp[1 << 16], d[1 << 16];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
    cin >> n; n2 = 1 << n;
    vvi a(n, vi(n));
    cin >> a;

    d[0] = 0;
    for(int s = 1; s < n2; s++) {
        int j = s&-s;
        int m = s^j;
        j = __builtin_popcount(j-1);
        d[s] = d[m];
        while(m) {
            int k = m&-m;
            d[s] += a[__builtin_popcount(k-1)][j];
            m ^= k;
        }
    }

    for(int s = 1; s < n2; s++) {
        dp[s] = d[s];
        for(int sm = s; sm; sm = (sm - 1)&s) 
            dp[s] = max(dp[s], dp[s^sm] + d[sm]);
    }
    cout << dp[n2-1];
}