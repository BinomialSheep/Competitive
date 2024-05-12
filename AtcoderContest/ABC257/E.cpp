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
    int mn = 1e9;
    int idx = -1;
    rep(i, 9) {
      if (C[i] <= mn) {
        mn = C[i];
        idx = i + 1;
      }
    }
    if (mn > N) {
      cout << 0 << endl;
      return;
    }

    // 暫定解
    string ans = "";
    rep(i, N / mn) {
      //
      ans += to_string(idx);
    }

    //
    int money = N % mn;

    debug(money);

    int keta = 0;
    while (true) {
      int flag = 0;
      for (int i = 9; i > idx; i--) {
        if (money + C[idx - 1] >= C[i - 1]) {
          ans[keta] = (char)('0' + i);
          keta++;
          money -= (C[i - 1] - C[idx - 1]);
          flag = 1;
          break;
        }
      }
      if (!flag) break;
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