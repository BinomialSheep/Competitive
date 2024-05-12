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
    int N, L, R;
    cin >> N >> L >> R;
    vl A(N);
    rep(i, N) cin >> A[i];
    /* solve */
    vl preA(N);
    rep(i, N) {
      if (i == 0) {
        preA[i] = A[i];
      } else {
        preA[i] = preA[i - 1] + A[i];
      }
    }
    ll Ls = 0;
    int Li = -1;
    rep(i, N) {
      Ls += L;
      if (Ls <= preA[i]) {
        Li = i;
      }
    }
    ll Rs = 0;
    int Ri = -1;
    rep(i, N) {
      Rs += R;
      if (i == N - 1 && Rs < preA[N - 1]) {
        Ri = i;
      } else if (Rs < preA[N - 1] - preA[N - 2 - i]) {
        Ri = i;
      }
    }

    if (Ri != -1) Ri = N - Ri;
    debug(preA, Li, Ri);
    // 領域が被っていない場合
    if (Li == -1) {
      if (Ri == -1) {
        cout << preA[N - 1] << endl;
        return;
      }
      for (int i = Ri; i < N - 1; i++) {
        A[i] = R;
      }
      ll ans = 0;
      rep(i, N) ans += A[i];
      cout << ans << endl;
      return;
    }
    if (Ri == -1) {
      for (int i = 0; i <= Li; i++) {
        A[i] = L;
      }
      ll ans = 0;
      rep(i, N) ans += A[i];
      cout << ans << endl;
      return;
    }

    if (Li < Ri) {
      for (int i = 0; i <= Li; i++) {
        A[i] = L;
      }
      for (int i = Ri; i < N - 1; i++) {
        A[i] = R;
      }
      ll ans = 0;
      rep(i, N) ans += A[i];
      cout << ans << endl;
    }
    // 領域が被っている場合は両方試す
    // Lを固定した場合

    Rs = 0;
    int Ri2 = -1;
    for (int i = N - 1; i > Li; i--) {
      Rs += R;
      if (Rs < preA[N - 1] - preA[i - 1]) {
        Ri2 = i;
      }
    }
    ll ans1 = 0;
    rep(i, N) {
      if (i <= Li)
        ans1 += L;
      else if (i <= Ri2)
        ans1 += A[i];
      else
        ans1 += R;
    }
    // Rを固定した場合
    Ls = 0;
    int Li2 = -1;
    rep(i, Ri) {
      Ls += L;
      if (Ls <= preA[i]) {
        Li2 = i;
      }
    }
    ll ans2 = 0;
    rep(i, N) {
      if (i <= Li2)
        ans2 += L;
      else if (i <= Ri)
        ans2 += A[i];
      else
        ans2 += R;
    }
    ll ans = ans1;
    chmin(ans, ans2);

    debug(Li2, Ri2, ans1, ans2);

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