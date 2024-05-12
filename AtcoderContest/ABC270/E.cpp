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
    int N;
    ll K;
    cin >> N >> K;
    vl A(N);
    rep(i, N) cin >> A[i];

    /* solve */
    auto llMin = [](ll a, ll b) { return a < b ? a : b; };

    auto isOK = [&](ll m) {
      ll cnt = 0;
      rep(i, N) cnt += llMin(A[i], m);
      if (cnt >= K) return true;
      return false;
    };

    ll ng = 0;
    ll ok = 1e12 + 1;
    while (abs(ok - ng) > 1) {
      ll mid = (ok + ng) / 2;
      if (isOK(mid)) {
        ok = mid;
      } else {
        ng = mid;
      }
    }
    // ok周目で終わる
    vl ans(N);
    --ok;
    rep(i, N) {
      if (A[i] >= ok) {
        ans[i] = A[i] - ok;
        K -= ok;
      } else {
        ans[i] = 0;
        K -= A[i];
      }
    }
    rep(i, N) {
      if (ans[i] > 0) ans[i]--, K--;
      if (K == 0) break;
    }

    /* output */
    rep(i, N) cout << ans[i] << " ";
    cout << endl;
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