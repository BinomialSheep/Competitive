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
  int N;
  vi T;
  int ans = INFTY;
  set<pii> memo;
  int sum = 0;

  void dfs(int a, int b, int idx) {
    if (idx == N) {
      chmin(ans, abs(a - b));
      return;
    }
    if (memo.count(make_pair(a, idx))) return;

    dfs(a + T[idx], b, idx + 1);
    memo.insert(make_pair(a + T[idx], idx));
    dfs(a, b + T[idx], idx + 1);
    memo.insert(make_pair(a, idx));
  }

  void solve() {
    /* input */
    cin >> N;
    T.resize(N);

    rep(i, N) cin >> T[i];

    /* solve */
    rep(i, N) sum += T[i];
    dfs(0, 0, 0);

    /* output */
    cout << (sum - ans) / 2 + ans << endl;
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