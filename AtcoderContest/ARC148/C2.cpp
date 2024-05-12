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
  void solve() {
    /* input */
    int N, Q;
    cin >> N >> Q;
    vvi G(N);
    vi parent(N);
    rep(i, N - 1) {
      int P;
      cin >> P;
      --P;
      parent[i + 1] = P;
      G[P].push_back(i + 1);
    }

    vi child(N);

    auto rec = [&](auto f, int v) -> void {
      if (G[v].empty()) {
        child[v] = 0;
        return;
      }
      for (auto u : G[v]) {
        f(f, u);
        child[v] += child[u] + 1;
      }
    };

    rec(rec, 0);
    // debug(G);
    // debug(child);
    // debug(parent);

    /* solve */

    rep(qi, Q) {
      int M;
      cin >> M;
      set<int> st;
      map<int, int> chil;
      vi V(M);
      rep(i, M) {
        cin >> V[i];
        V[i]--;
        st.insert(V[i]);
        if (V[i] != 0) chil[parent[V[i]]]++;
      }
      debug(st);

      // sort(all(V));
      vpii VP;
      rep(i, M) VP.emplace_back(child[V[i]], V[i]);
      // sort(all(VP));

      rep(i, V.size()) assert(0 <= V[i] && V[i] < N);
      sort(all(V), [&](int l, int r) { return child[l] < child[r]; });

      //   debug(V);
      debug(VP);

      int ans = 0;
      rep(i, M) {
        auto V2 = VP[i].second;
        if (V2 != 0 && st.count(parent[V2]) != 0) {
          // 自分と親が両方表なら、親に任せる
          ans += (int)G[V2].size();
          if (chil.count(V2)) ans -= chil[V2];
        } else {
          // 自分だけが表なら、裏の子をひっくり返してから自分もひっくり返す
          debug(i, V2, G[V2].size(), chil[V2]);
          ans += (int)G[V2].size() + 1;
          if (chil.count(V2)) ans -= chil[V2];
        }
      }
      cout << ans << "\n";
    }
    /* output */
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