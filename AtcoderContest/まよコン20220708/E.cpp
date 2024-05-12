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
    cin >> N;
    vi C(9);
    rep(i, 9) cin >> C[i];

    /* solve */
    int idx = 0;
    int value = INFTY;
    rep(i, 9) {
      if (value >= C[i]) {
        idx = i + 1;
        value = C[i];
      }
    }
    // debug(idx, value);

    string ans = "";
    int money = N;
    while (money - C[idx - 1] >= 0) {
      ans.push_back((char)('0' + idx));
      money -= C[idx - 1];
    }
    debug(ans);

    // お釣りで銭湯をいじる
    rep(j, N) {
      debug(money);
      int flag = true;
      int idx2 = -1;
      rep(i, 9) {
        if ((idx - 1) < i && C[i] <= C[idx - 1] + money) {
          idx2 = i;
          flag = false;
        }
      }
      if (flag) break;
      ans[j] = (char)('0' + idx2 + 1);
      money -= (C[idx2] - C[idx - 1]);
    }
    cout << ans << endl;

    /* output */
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