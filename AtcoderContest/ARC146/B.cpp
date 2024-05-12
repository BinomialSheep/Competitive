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

ll llMin(ll a, ll b) { return (a >= b ? b : a); }

struct Solver {
  void solve() {
    /* input */
    int N, M, K;
    cin >> N >> M >> K;
    vl A(N);
    rep(i, N) cin >> A[i];

    /* solve */

    vl B;
    int start = -1;

    for (int i = 32; i >= 1; i--) {
      ll div = 1LL << i;
      ll mul = 1LL << (i - 1);
      vl tmp(N);
      rep(j, N) tmp[j] = A[j] % div;
      sort(tmp.rbegin(), tmp.rend());
      ll sum = 0;
      rep(j, K) sum += llMin(mul, tmp[j]);

      assert(mul * K >= 0);

      if (sum + M >= mul * K) {
        debug(i, sum, M, div, mul, K);
        start = i;
        rep(j, K) B.push_back(tmp[j]);
        break;
      }
    }
    if (start == -1) {
      cout << 0 << endl;
      return;
    }

    ll ans = 0;
    for (int ni = start; ni >= 1; ni--) {
      assert(M >= 0);
      // 判定
      ll now = 1LL << (ni - 1);
      ll sum = 0;
      rep(i, (int)B.size()) {
        assert(B[i] < now * 2);
        sum += llMin(B[i], now);
      }
      assert(now * K >= 0);
      if (ni == start) assert(sum + M >= now * K);
      if (sum + M >= now * K) {
        // 足し引き
        ans += now;
        rep(i, (int)B.size()) {
          if (B[i] >= now) {
            B[i] -= now;
          } else {
            M -= now - B[i];
            B[i] = 0;
          }
        }
      } else {
        rep(i, (int)B.size()) {
          if (B[i] >= now) B[i] -= now;
        }
      }
    }

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