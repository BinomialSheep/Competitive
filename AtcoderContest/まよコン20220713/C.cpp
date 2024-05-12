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
    int N, M;
    cin >> N >> M;

    vvi G(N);

    set<pii> st;

    rep(i, M) {
      int A, B;
      cin >> A >> B;
      --A;
      --B;
      if (A > B) swap(A, B);
      if (!st.count(make_pair(A, B))) {
        st.insert(make_pair(A, B));
        G[A].push_back(B);
        G[B].push_back(A);
      }
    }

    /* solve */
    if (M == 0) {
      cout << "Yes" << endl;
      return;
    }

    rep(i, N) {
      if (G[i].size() >= 3) {
        cout << "No" << endl;
        return;
      }
    }

    vi color(N);
    rep(i, N) {
      if (G[i].size() == 0) continue;
      if (color[i] == 1) continue;
      queue<int> q;
      q.push(i);
      int last = -1;

      while (!q.empty()) {
        int v = q.front();
        q.pop();
        color[v] = 1;
        if (i != v && G[v].size() == 1) break;
        for (auto u : G[v]) {
          if (last == u) continue;
          if (color[u]) {
            cout << "No" << endl;
            return;
          }
          q.push(u);
          break;
        }
        last = v;
      }
    }

    cout << "Yes" << endl;

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