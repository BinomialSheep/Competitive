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
    vs A(2 * N);
    rep(i, 2 * N) cin >> A[i];

    /* solve */
    vpii p;
    rep(i, 2 * N) p.emplace_back(0, i);

    rep(i, M) {
      for (int j = 0; j < 2 * N; j += 2) {
        char c1 = A[p[j].second][i];
        char c2 = A[p[j + 1].second][i];

        if ((c1 == 'G' && c2 == 'C') || (c1 == 'C' && c2 == 'P') ||
            (c1 == 'P' && c2 == 'G')) {
          // c1の勝ち
          A[p[j].first--];
        } else if ((c2 == 'G' && c1 == 'C') || (c2 == 'C' && c1 == 'P') ||
                   (c2 == 'P' && c1 == 'G')) {
          A[p[j + 1].first--];
        }
      }
      sort(p.begin(), p.end());
    }
    /* output */
    rep(i, 2 * N) cout << p[i].second + 1 << '\n';
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