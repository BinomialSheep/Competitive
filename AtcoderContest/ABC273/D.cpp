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
    int H, W, rs, cs;
    cin >> H >> W >> rs >> cs;
    int N;
    cin >> N;
    map<int, vector<int>> wallR;
    map<int, vector<int>> wallC;
    rep(i, N) {
      int r, c;
      cin >> r >> c;
      wallR[r].push_back(c);
      wallC[c].push_back(r);
    }
    for (auto &p : wallR) sort(all(p.second));
    for (auto &p : wallC) sort(all(p.second));
    // debug(wallR);
    // debug(wallC);

    /* solve */
    int nr = rs, nc = cs;
    int Q;
    cin >> Q;
    rep(i, Q) {
      char d;
      int l;
      cin >> d >> l;
      if (d == 'L') {
        if (wallR.count(nr) == 0) {
          nc = max(1, nc - l);
        } else {
          auto it = upper_bound(all(wallR[nr]), nc);
          if (it == wallR[nr].begin()) {
            nc = max(1, nc - l);
          } else {
            --it;
            nc = max(*it + 1, nc - l);
          }
        }
      } else if (d == 'R') {
        if (wallR.count(nr) == 0) {
          nc = min(W, nc + l);
        } else {
          auto it = upper_bound(all(wallR[nr]), nc);
          if (it == wallR[nr].end()) {
            nc = min(W, nc + l);
          } else {
            nc = min(*it - 1, nc + l);
          }
        }
      } else if (d == 'U') {
        if (wallC.count(nc) == 0) {
          nr = max(1, nr - l);
        } else {
          auto it = upper_bound(all(wallC[nc]), nr);
          if (it == wallC[nc].begin()) {
            nr = max(1, nr - l);
          } else {
            --it;
            nr = max(*it + 1, nr - l);
          }
        }
      } else {
        if (wallC.count(nc) == 0) {
          nr = min(H, nr + l);
        } else {
          auto it = upper_bound(all(wallC[nc]), nr);
          if (it == wallC[nc].end()) {
            nr = min(H, nr + l);
          } else {
            nr = min(*it - 1, nr + l);
          }
        }
      }
      printf("%d %d\n", nr, nc);
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