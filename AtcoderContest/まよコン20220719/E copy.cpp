#include <bits/stdc++.h>
// デバッグ用マクロ：https://naskya.net/post/0002/
#ifdef LOCAL
#include <debug_print.hpp>
#define debug(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (static_cast<void>(0))
#endif
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
// #include <atcoder/all>
// using namespace atcoder;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()
// #define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

template <typename T>
inline bool chmax(T &a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T &a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

struct Solver {
  vl dijkstra(int V, int r, vector<vector<pii>> &G) {
    vl dist(V);
    // 距離を初期化
    rep(i, V) dist[i] = 4e18;
    // 優先度付きキューに、(距離, 頂点番号)の組を入れる
    using pli = pair<ll, int>;
    priority_queue<pli, vector<pli>, greater<pli>> q;
    // 始点
    q.emplace(0, r);
    dist[r] = 0;
    while (!q.empty()) {
      int pos = q.top().second;
      q.pop();
      rep(i, (int)G[pos].size()) {
        int to = G[pos][i].first;
        int cost = G[pos][i].second;
        if (chmin(dist[to], dist[pos] + cost)) {
          q.emplace(dist[to], to);
        }
      }
    }
    return dist;
  }

  void solve() {
    /* input */
    int N, M, s, t;
    cin >> N >> M >> s >> t;
    vector<vpii> G(N);
    vector<vpii> rev(N);

    rep(i, M) {
      int A, B, C;
      cin >> A >> B >> C;
      --A, --B;
      G[A].emplace_back(B, C);
      rev[B].emplace_back(A, C);
    }

    /* solve */
    vl dist = dijkstra(N, s, G);

    /* output */
    



    cout << endl;
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