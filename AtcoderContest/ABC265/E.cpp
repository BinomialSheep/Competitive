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
#include <atcoder/all>
using namespace atcoder;
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
    int A, B, C, D, E, F;
    cin >> A >> B >> C >> D >> E >> F;
    using pll = pair<ll, ll>;
    set<pll> st;
    rep(i, M) {
      ll x, y;
      cin >> x >> y;
      st.insert(make_pair(x, y));
    }

    using mint = modint998244353;
    /* solve */

    vector<map<pll, mint>> dp(N + 1);
    pll tmp = make_pair(0, 0);
    dp[0][tmp] = 1;

    rep(i, N) {
      for (auto p : dp[i]) {
        ll x = p.first.first;
        ll y = p.first.second;

        pll xy1 = make_pair(x + A, y + B);
        pll xy2 = make_pair(x + C, y + D);
        pll xy3 = make_pair(x + E, y + F);
        if (st.count(xy1) == 0) {
          dp[i + 1][xy1] += p.second;
        }
        if (st.count(xy2) == 0) {
          dp[i + 1][xy2] += p.second;
        }
        if (st.count(xy3) == 0) {
          dp[i + 1][xy3] += p.second;
        }
      }
    }

    mint ans = 0;
    for (auto p : dp[N]) ans += p.second;

    /* output */
    cout << ans.val() << endl;
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