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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    int MOD = 1e9 + 7;
    rep(ti, T) {
      /* input */
      int N;
      cin >> N;
      vl A(N), B(N);
      rep(i, N) cin >> A[i] >> B[i];
      int Q;
      cin >> Q;
      vl X(Q), Y(Q);
      rep(i, Q) cin >> X[i] >> Y[i];
      sort(all(A));
      sort(all(B));
      sort(all(X));
      sort(all(Y));

      ll ans = 0;

      int a = 0, x = 0;
      stack<ll> st;
      ll now = 0;
      ll sum = 0;
      while (x < Q) {
        if (X[x] < a[a]) {
          while(!st.empty()) {
            auto v = st.top();
            st.pop();
            sum += v;
            now += now;
            now += 2 * sum;
            now += v * v;
            now %= MOD;
          }


          x++;
        } else {
          st.push(A[a]);
          a++;
        }
      }
      ans += now;
      ans %= MOD;
      // 右側

      // bとyについても



      ll ans = 0;
      rep(a, 3001) rep(x, 3001) ans =
          (ans + As[a] * Xs[x] * abs(x - a) * abs(x - a)) % MOD;
      rep(b, 3001) rep(y, 3001) ans =
          (ans + Bs[b] * Ys[y] * abs(y - b) * abs(y - b)) % MOD;

      /* solve */

      /* output */
      printf("Case #%d: %lld\n", ti + 1, ans);
    }
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