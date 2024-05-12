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
    string S;
    cin >> S;
    vi W(N);
    rep(i, N) cin >> W[i];

    /* solve */
    vector<pii> ps;
    rep(i, N) { ps.emplace_back(W[i], S[i] - '0'); }
    sort(all(ps));

    vi preChild(N + 1);
    rep(i, N) {
      if (ps[i].second == 0) preChild[i + 1] = 1;
      preChild[i + 1] += preChild[i];
    }
    vi preAdult(N + 1);
    rep(i, N) {
      if (ps[i].second == 1) preAdult[i + 1] = 1;
      preAdult[i + 1] += preAdult[i];
    }

    int child = 0;
    rep(i, N) if (S[i] == '0') child++;
    int adult = N - child;

    debug(ps);
    debug(preChild);
    debug(preAdult);

    int ans = 0;
    rep(i, N + 1) {
      // ps[i].first +0.1に置く
      // childと正しく判定
      if (i != 0 && ps[i].first == ps[i - 1].first) continue;
      int c = preChild[i];
      // adultと正しく判定
      int a = adult - preAdult[i];
      //
      debug(i, a, c);
      chmax(ans, c + a);
    }

    /* output */
    cout << ans << endl;
  }
};

int main() {
  int ts = 3;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
  }
  return 0;
}