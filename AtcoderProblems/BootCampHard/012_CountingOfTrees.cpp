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
    int N;
    cin >> N;
    vi D(N);
    rep(i, N) cin >> D[i];

    /* solve */
    if (D[0] != 0) {
      cout << 0 << endl;
      return;
    }

    sort(all(D));

    vpii lan;
    rep(i, N) {
      if (i == 0) {
        lan.emplace_back(D[i], 1);
        continue;
      }
      if (lan.back().first == D[i]) {
        lan.back().second++;
      } else {
        lan.emplace_back(D[i], 1);
      }
    }
    // debug(lan);

    using mint = modint998244353;
    mint ans = 1;
    mint last = 1;

    int fst = 0;
    for (auto p : lan) {
      if (p.first != fst) {
        cout << 0 << endl;
        return;
      }
      fst++;
      if (p.first == 0) {
        if (p.second != 1) {
          cout << 0 << endl;
          return;
        }
        continue;
      }
      mint tmp = 1;
      rep(i, p.second) { tmp *= last; }
      ans *= tmp;

      last = p.second;
    }

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