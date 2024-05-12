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
    vi A(N);
    rep(i, N) cin >> A[i];

    /* solve */
    map<int, int> right;
    rep(i, N) right[A[i]]++;

    map<int, int> left;
    map<int, int> both;

    ll ans = 0;
    for (int j = 1; j <= N - 2; j++) {
      if (right.count(A[j - 1])) {
        if (right[A[j - 1]] == 1) {
          // leftに移る
          left[A[j - 1]] = 1;
          right.erase(A[j - 1]);
        } else {
          // bothに移る
          both[A[j - 1]] = right[A[j - 1]] - 1;
          right.erase(A[j - 1]);
        }
      } else if (both[A[j - 1]] == 1) {
        // rightに移る
        both.erase(A[j - 1]);
        left[A[j - 1]] = 1;
      } else {
        both[A[j - 1]]--;
      }
      // 答えの更新
      ll r = right.size();
      if (right.count(A[j])) r--;
      ll l = left.size();
      if (left.count(A[j])) l--;
      ll b = both.size();
      if (both.count(A[j])) b--;
      //
      ans += r * l;
      ans += r * b;
      ans += b * l;
      ans += b * (b - 1);
      debug(left, both, right);
      debug(l, b, r);
      debug(j, ans);
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