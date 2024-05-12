#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
using vvvi = vector<vector<vector<int>>>;
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

template <typename T>
inline bool chmax(T &a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T &a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

int main() {
  /* input */
  int V, E;
  cin >> V >> E;

  vvi G(V, vi(V, INFTY));
  rep(i, E) {
    int s, t, d;
    cin >> s >> t >> d;
    G[s][t] = d;
  }

  /* solve */
  // 1 << Vで通った頂点を表す
  // dp[bit][start][i] usedがbitで今iにいる時の最小値
  vvvi dp((1 << V), vvi(V, vi(V, INFTY)));
  //
  rep(i, V) { dp[1 << i][i][i] = 0; }

  rep(bit, 1 << V) {
    rep(start, V) {
      rep(i, V) {
        // 各状態（探索済み集合、始点、現在地）
        // 探索済みに今の頂点が含まれていないケースは存在しない
        if (!(bit & (1 << i))) continue;
        // 有向辺の先に配る
        rep(j, V) {
          // 辺がないなら無視する
          if (G[i][j] == INFTY) continue;
          // 探索済みなら無視する
          if (bit & (1 << j)) continue;
          // 辺があるなら更新
          int nexBit = bit | (1 << j);
          chmin(dp[nexBit][start][j], dp[bit][start][i] + G[i][j]);
        }
      }
    }
  }

  // rep(start, V) {
  //   cout << "始点：" << start << endl;
  //   rep(bit, 1 << V) {
  //     cout << bitset<4>(bit) << " ";
  //     rep(i, V) { cout << dp[bit][start][i] << " "; }
  //     cout << endl;
  //   }
  // }

  ll ans = INFTY;
  int bit = (1 << V) - 1;
  rep(start, V) {
    rep(i, V) {
      if (G[i][start] != INFTY) {
        chmin(ans, (ll)dp[bit][start][i] + G[i][start]);
      }
    }
  }

  /* output */
  cout << (ans == INFTY ? -1 : ans) << endl;

  return 0;
}