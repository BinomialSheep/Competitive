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
    int N, K;
    cin >> N >> K;
    vi P(N);
    rep(i, N) cin >> P[i];

    /* solve */
    vi ans(N + 1, -1);
    map<int, int> mp;
    vi tmpAns(N + 1);

    rep(i, N) {
      auto it = mp.lower_bound(P[i]);
      if (it == mp.end()) {
        mp[P[i]] = 1;
      } else {
        auto p = *it;
        auto tmp = p.second;
        mp.erase(it);
        tmpAns[p.first] = P[i];
        mp[P[i]] = tmp + 1;
      }
      if (mp[P[i]] == K) {
        mp.erase(P[i]);
        ans[P[i]] = i + 1;
      }
    }

    rep(i, N + 1) {
      if (tmpAns[i] != 0) {
        ans[i] = ans[tmpAns[i]];
      }
    }
    /* output */
    for (int i = 1; i <= N; i++) cout << ans[i] << "\n";
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