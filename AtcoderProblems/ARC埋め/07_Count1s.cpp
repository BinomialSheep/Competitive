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
    int N;
    cin >> N;
    vi A(N);
    rep(i, N) cin >> A[i];

    /* solve */
    int cnt = 0;
    rep(i, N) if (A[i]) cnt++;

    // 最小値と最大値だけ考えれば、真ん中は全部作れる
    int mx = 0;
    int now = 0;
    int right = 0;
    rep(left, N) {
      if (right < left) {
        right = left;
        now = 0;
      }
      while (right < N && now >= 0) {
        debug(left, right);
        A[right] == 1 ? now++ : now--;
        chmax(mx, now);
        right++;
      }
      // leftを除く
      A[left] == 1 ? now-- : now++;
      chmax(mx, now);
    }

    int mn = 0;
    now = 0;
    right = 0;
    rep(left, N) {
      if (right < left) {
        right = left;
        now = 0;
      }
      while (right < N && now >= 0) {
        debug(left, right);
        A[right] == 0 ? now++ : now--;
        chmax(mn, now);
        right++;
      }
      // leftを除く
      A[left] == 0 ? now-- : now++;
      chmax(mn, now);
    }
    debug(mx, mn);
    int ansMn = cnt - mx;
    int ansMx = cnt + mn;
    int ans = ansMx - ansMn + 1;
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