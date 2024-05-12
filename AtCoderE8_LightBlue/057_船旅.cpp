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

struct Solver {
  int dijkstra(int V, int r, int goal, vvi &G) {
    vi dist(V);
    rep(i, V) dist[i] = INFTY;
    // (距離, 頂点番号)の組を入れてく
    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    // 始点
    q.emplace(0, r);
    dist[r] = 0;
    while (!q.empty()) {
      int pos = q.top().second;
      if (pos == goal) {
        return dist[pos];
      }
      q.pop();

      rep(i, V) {
        int to = i;
        int cost = G[pos][i];
        if (chmin(dist[to], dist[pos] + cost)) {
          q.emplace(dist[to], to);
        }
      }
    }
    return -1;
  }

  void solve() {
    int n, k;
    cin >> n >> k;

    vector<vector<int>> G(n, vector<int>(n, INFTY));

    rep(ki, k) {
      /* input */
      int num;
      cin >> num;
      if (num == 0) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        // aからbまでダイクストラ
        int dist = dijkstra(n, a, b, G);
        cout << dist << endl;

      } else {
        int c, d, e;
        cin >> c >> d >> e;
        --c;
        --d;
        chmin(G[c][d], e);
        chmin(G[d][c], e);
      }
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