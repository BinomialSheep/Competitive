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
using pll = pair<ll, ll>;
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
  void solve() {
    /* input */
    int N, M;
    cin >> N >> M;
    vl A(N);
    rep(i, N) cin >> A[i];

    vvi G(N);

    rep(i, M) {
      int U, V;
      cin >> U >> V;
      --U, --V;
      G[U].push_back(V);
      G[V].push_back(U);
    }

    /* solve */
    ll ans = -1;

    using pli = pair<ll, int>;
    using vpli = vector<pli>;
    priority_queue<pli, vpli, greater<pli>> pq;
    vl mp(N);
    vb B(N);

    rep(i, N) {
      ll tmp = 0;
      for (auto u : G[i]) {
        tmp += A[u];
      }
      pq.emplace(tmp, i);
      mp[i] = tmp;
    }

    while (!pq.empty()) {
      auto p = pq.top();
      pq.pop();
      if (B[p.second] || mp[p.second] != p.first) continue;
      chmax(ans, p.first);

      for (auto u : G[p.second]) {
        if (B[u]) continue;
        mp[u] -= A[p.second];
        pq.emplace(mp[u], u);
      }
      B[p.second] = true;
    }

    /* output */
    cout << ans << endl;
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