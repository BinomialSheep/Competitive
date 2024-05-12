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
    int H1, W1;
    cin >> H1 >> W1;
    vvi A(H1, vi(W1));
    rep(i, H1) rep(j, W1) cin >> A[i][j];
    int H2, W2;
    cin >> H2 >> W2;
    vvi B(H2, vi(W2));
    rep(i, H2) rep(j, W2) cin >> B[i][j];

    /* solve */
    rep(bit, 1 << H1) {
      if (__builtin_popcount(bit) != H2) continue;
      rep(bit2, 1 << W1) {
        if (__builtin_popcount(bit2) != W2) continue;
        // debug(bit, bit2);

        vi hs;
        vi ws;
        rep(i, H1) {
          if (bit & (1 << i)) {
            hs.push_back(i);
          }
        }
        rep(j, W1) {
          if (bit2 & (1 << j)) {
            ws.push_back(j);
          }
        }

        // debug(hs);
        // debug(ws);

        int flag = true;
        rep(i, H2) rep(j, W2) {
          if (B[i][j] != A[hs[i]][ws[j]]) flag = false;
        }
        if (flag) {
          cout << "Yes" << endl;
          return;
        }
      }
    }

    cout << "No" << endl;

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