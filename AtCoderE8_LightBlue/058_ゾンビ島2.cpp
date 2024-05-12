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

vvi G;

struct Solver {
  void bfs(vi &C, int S, vi &danger) {
    // 距離Sまでやる
    queue<pair<int, int>> q;
    unordered_set<int> st;
    rep(i, (int)C.size()) {
      st.insert(C[i]);
      q.emplace(C[i], 0);
    }
    while (!q.empty()) {
      auto p = q.front();
      q.pop();
      st.insert(p.first);
      if (p.second < S) {
        for (auto u : G[p.first]) {
          if (st.count(u)) continue;
          danger[u] = 1;
          q.emplace(u, p.second + 1);
        }
      }
    }
  }

  vl dijkstra(int V, int r, vector<vector<pii>> &G2) {
    vl dist(V);
    rep(i, V) dist[i] = (1LL << 62);
    using pli = pair<ll, int>;
    priority_queue<pli, vector<pli>, greater<pli>> q;
    //
    q.emplace(0, r);
    dist[r] = 0;
    while (!q.empty()) {
      int pos = q.top().second;
      if (pos == V - 1) return dist;
      q.pop();
      for (auto us : G2[pos]) {
        int to = us.first;
        int cost = us.second;
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

    G.resize(N);
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
    // 各ゾンビがいる頂点からBFSすればいい
    bfs(C, S, danger);
    // ゾンビがいる街そのものは訪れることができない
    rep(ci, K) danger[C[ci]] = -1;

    // rep(i, N) { cout << danger[i]; }
    // cout << endl;
    // グラフを整形

    vector<vector<pii>> G2(N);

    rep(i, N) {
      if (danger[i] == -1) continue;
      for (auto to : G[i]) {
        if (danger[to] == -1) continue;
        int cost;
        if (to == N - 1) {
          cost = 0;
        } else if (danger[to] > 0) {
          cost = Q;
        } else {
          cost = P;
        }
        G2[i].emplace_back(to, cost);
      }
    }

    // 最小の費用を求める
    vl dist = dijkstra(N, 0, G2);

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