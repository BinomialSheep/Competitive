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
#include <atcoder/all>
using namespace atcoder;
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
    int N, M, Q;
    cin >> N >> M >> Q;

    // 到達可能集合
    dsu uf(N);
    //
    vector<vpii> G(N);
    rep(i, M) {
      int A, B, C;
      cin >> A >> B >> C;
      --A;
      --B;
      uf.merge(A, B);

      G[A].emplace_back(B, C);
    }
    vi Xs(Q), Ys(Q);
    map<int, vector<int>> qmap;
    rep(qi, Q) {
      int X, Y;
      cin >> X >> Y;
      --X, --Y;
      Xs[qi] = X;
      Ys[qi] = Y;
      if (uf.same(X, Y)) {
        qmap[X].push_back(Y);
      }
    }

    /* solve */
    map<int, vpii> dist;

    map<int, pii> mp;
    map<int, int> mp2;
    int gidx = 0;
    vector<vvi> sccs;
    for (vi vec : uf.groups()) {
      scc_graph graph(vec.size());
      map<int, int> inv;
      int idx = 0;
      for (int from : vec) {
        if (mp.count(from) == 0) {
          mp[from] = make_pair(gidx, idx);
          inv[idx] = from;
          idx++;
        }
        for (auto edge : G[from]) {
          int to = edge.first;
          if (mp.count(to) == 0) {
            mp[to] = make_pair(gidx, idx);
            inv[idx] = to;
            idx++;
          }
          graph.add_edge(mp[from].second, mp[to].second);
        }
      }
      sccs.push_back(graph.scc());

      int idx = 0;
      set<vi> st;
      vi now;
      for (auto vec : sccs[gidx]) {
        if (vec.size() > 2) {
          if (now.size() >= 2) {
            st.insert(now);
          }
          now.clear();
        } else {
          now.push_back(vec[0]);
        }
      }
    }
    gidx++;
  }

  rep(qi, Q) {
    int X, Y;
    cin >> X >> Y;
    --X, --Y;
    if (!uf.same(X, Y)) {
      cout << "nan" << endl;
      continue;
    }
    assert(mp[X].first == mp[Y].first);

    int gidx = mp[X].first;
    cout << "inf" << endl;
  }

  /* output */
}
}
;

int main() {
  int ts = 1;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
  }
  return 0;
}