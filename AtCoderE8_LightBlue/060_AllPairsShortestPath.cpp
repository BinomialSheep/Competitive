#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vb = vector<bool>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
using vvb = vector<vector<bool>>;
using vvvi = vector<vector<vector<int>>>;
using pii = pair<int, int>;
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 30)
#define INFTYLL (1LL << 60)
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

/* ワーシャルフロイド
   ワーシャル・フロイド
   全点対間最短距離
   warshallFloyd
   Floyd
*/

// 頂点k個まで使った時のfrom i to jの最短経路というdp
// 負閉路があるならiからiへの負の経路が存在

struct Solver {
  void floyd(int V, vvl &G) {
    rep(i, V) G[i][i] = 0;

    rep(k, V) rep(i, V) {
      if (G[i][k] == INFTYLL) continue;
      rep(j, V) {
        //
        if (G[k][j] == INFTYLL) continue;
        chmin(G[i][j], G[i][k] + G[k][j]);
      }
    }
  }

  void solve() {
    /* input */
    int V, E;
    cin >> V >> E;

    vvl G(V, vl(V, INFTYLL));

    rep(i, E) {
      int s, t, d;
      cin >> s >> t >> d;
      G[s][t] = d;
    }

    /* solve */
    floyd(V, G);

    /* output */
    // 負閉路チェック
    rep(i, V) {
      if (G[i][i] < 0) {
        cout << "NEGATIVE CYCLE" << endl;
        return;
      }
    }
    rep(i, V) {
      rep(j, V) {
        if (G[i][j] == INFTYLL) {
          cout << "INF";
        } else {
          cout << G[i][j];
        }
        if (j != V - 1) cout << " ";
      }
      cout << endl;
    }
  }
};

int main() {
  int ts = 1;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
  }
  return 0;
}