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
  void dfs(int v, int depth, int S, vvi &G, vi &danger, int start) {
    if (danger[v] == start) return;
    danger[v] = start;
    if (depth == S) return;
    for (auto u : G[v]) {
      dfs(u, depth + 1, S, G, danger, start);
    }
  }

  vl dijkstra(int V, int r, vvi &G, vi &danger, int P, int Q) {
    vl dist(V);
    rep(i, V) dist[i] = (1LL << 60);
    using pli = pair<ll, int>;
    priority_queue<pli, vector<pli>, greater<pli>> q;
    //
    q.emplace(0, r);
    dist[0] = 0;
    while (!q.empty()) {
      int pos = q.top().second;
      q.pop();
      for (auto to : G[pos]) {
        if (danger[to] == -1) continue;
        int cost;
        if (to == V - 1) {
          cost = 0;
        } else if (danger[to] > 0) {
          cost = Q;
        } else {
          cost = P;
        }
        // printf("%d %d %d\n", pos, to, cost);
        if (chmin(dist[to], dist[pos] + cost)) {
          q.emplace(dist[to], to);
        }
      }
    }
    return dist;
  }

  void solve() {
    /* input */
    int N, M, K, S;
    cin >> N >> M >> K >> S;
    int P, Q;
    cin >> P >> Q;
    vector<int> C(K);
    rep(i, K) {
      int tmp;
      cin >> tmp;
      C[i] = --tmp;
    }
    vvi G(N);
    rep(i, M) {
      int A, B;
      cin >> A >> B;
      --A;
      --B;
      G[A].push_back(B);
      G[B].push_back(A);
    }

    /* solve */
    // ゾンビが支配している頂点を求める
    vi danger(N);
    // 各ゾンビがいる頂点からDFSすればいい
    rep(ci, K) { dfs(C[ci], 0, S, G, danger, ci + 1); }
    // ゾンビがいる街そのものは訪れることができない
    rep(ci, K) danger[C[ci]] = -1;

    // rep(i, N) { cout << danger[i]; }
    // cout << endl;
    // グラフを整形
    

    // 最小の費用を求める
    vl dist = dijkstra(N, 0, G, danger, P, Q);

    // rep(i, N) cout << dist[i] << " ";
    // cout << endl;

    /* output */
    assert(dist[N - 1] >= 0);
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