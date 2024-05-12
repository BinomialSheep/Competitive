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
    int n;
    cin >> n;
    vi c(n);
    rep(i, n) cin >> c[i];

    /* solve */
    deque<pii> q;
    rep(i, n) {
      if (q.empty()) {
        q.emplace_back(c[i], 1);
        continue;
      }
      if (i % 2) {
        // 偶数ターン
        if (q.back().first == c[i]) {
          q.back().second++;
        } else {
          auto p = q.back();
          q.pop_back();
          if (q.empty()) {
            p.first ^= 1;
            p.second++;
            q.push_back(p);
          } else {
            q.back().second += p.second + 1;
          }
        }
      } else {
        // 奇数ターン
        if (q.back().first == c[i]) {
          q.back().second++;
        } else {
          q.emplace_back(c[i], 1);
        }
      }
    }
    // カウント
    ll ans = 0;
    rep(i, (int)q.size()) {
      if (!q[i].first) ans += q[i].second;
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