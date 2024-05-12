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
    ll N;
    int M;
    cin >> N >> M;

    if (M == 0) {
      cout << "Aoki" << endl;
      return;
    }

    vpii xys(M);
    rep(i, M) { cin >> xys[i].first >> xys[i].second; }
    sort(all(xys));

    /* solve */
    int cnt = 0;

    rep(i, M - 1) {
      if (xys[i + 1].first - xys[i].first == 5 &&
          xys[i + 1].second == xys[i].second)
        cnt++;
    }

    if (cnt > 0) {
      debug(false);
      
      cout << (cnt % 2 ? "Takahashi" : "Aoki") << endl;
      return;
    } else {
      ll turn = 0;
      turn += xys[0].first - 1;
      turn += N - xys[M - 1].first;
      turn %= 2;
      rep(i, M - 1) {
        ll diff = xys[i + 1].first - xys[i].first;
        if (diff == 1) continue;
        if (diff % 2) {
          if (xys[i + 1].second == xys[i].second) {
            turn++;
          } else {
            //
          }
        } else {
          if (xys[i + 1].second != xys[i].second) turn++;
        }
      }
      turn %= 2;
      cout << (turn ? "Takahashi" : "Aoki") << endl;
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