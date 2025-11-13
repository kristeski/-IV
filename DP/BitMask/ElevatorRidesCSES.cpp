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

int n, w;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
    cin >> n >> w;
    int n2 = 1 << n;
    vector<pair<ll, ll>> dp(n2, {2e9, 2e9});
    vi wei(n);
    cin >> wei;
    dp[0] = {1, 0};
    for(int s = 1; s < n2; s++) { 
        int m = s;
        while(m) {
            int i = m & -m;
            m^=i;
            pair<ll, ll> np = dp[s^i];
            i = __builtin_popcount(i-1);
            np.second += wei[i];
            if(np.second > w) {
                np.second = wei[i];
                np.first++;
            }
            dp[s] = min(dp[s], np);
        }
    }
    cout << dp[n2-1].first;

}