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
  vi dijkstra(int V, int r, vvi &G) {
    vi dist(V);
    rep(i, V) dist[i] = INFTY;
    //
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.emplace(0, r);
    dist[r] = 0;
    while (!q.empty()) {
      int pos = q.top().second;
      q.pop();
      rep(ui, V) {
        if (G[pos][ui] == 0) continue;
        int to = ui;
        int cost = G[pos][ui];
        if (chmin(dist[to], dist[pos] + cost)) {
          q.emplace(dist[to], to);
        }
      }
    }
    return dist;
  }

  void solve() {
    /* input */
    int N, K;
    cin >> N >> K;
    vi C(N);
    vi R(N);
    rep(i, N) cin >> C[i] >> R[i];

    vvi inG(N);
    rep(i, K) {
      int A, B;
      cin >> A >> B;
      --A;
      --B;
      inG[A].push_back(B);
      inG[B].push_back(A);
    }

    /* solve */
    // 各頂点からBFSして、グラフを作成する
    static vvi G(N, vi(N));

    rep(v, N) {
      queue<pii> q;
      q.emplace(v, 0);
      unordered_set<int> used;
      while (!q.empty()) {
        auto p = q.front();
        q.pop();
        used.insert(p.first);
        if (p.second == R[v]) break;
        for (auto u : inG[p.first]) {
          if (used.count(u)) continue;
          G[v][u] = C[v];
          q.emplace(u, p.second + 1);
        }
      }
    }

    // ダイクストラする
    vi dist = dijkstra(N, 0, G);

    /* output */
    cout << dist[N - 1] << endl;
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