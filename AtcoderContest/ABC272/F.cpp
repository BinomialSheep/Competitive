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
    string S, T;
    cin >> N >> S >> T;

    /* solve */
    deque<char> S2(N);
    rep(i, N) S2[i] = S[i];
    deque<char> T2(N);
    rep(i, N) T2[i] = T[i];
    vector<deque<char>> vec;
    rep(i, N) {
      vec.emplace_back(S2);
      S2.push_back(S2.front());
      S2.pop_front();
    }
    sort(all(vec));

    // debug(vec);

    ll ans = 0;

    rep(i, N) {
      auto it = upper_bound(all(vec), T2);
      if (it != vec.end()) {
        // debug(distance(vec.begin(), it));
        ans += distance(vec.begin(), it);
      } else {
        ans += N;
      }
      // debug(T2);
      // debug(ans);
      T2.push_back(T2.front());
      T2.pop_front();
      //
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