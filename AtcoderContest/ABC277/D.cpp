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
    vi A(N);
    rep(i, N) cin >> A[i];

    /* solve */
    vi B(N);
    rep(i, N) B[i] = A[i];
    rep(i, N) A[i] %= M;
    sort(all(A));
    dsu uf(N);

    rep(i, N - 1) {
      if (A[i + 1] - A[i] <= 1) uf.merge(i, i + 1);
    }
    if (A[0] == 0 && A[N - 1] == M - 1) uf.merge(N - 1, 0);

    int sz = uf.groups().size();
    map<int, int> mp;
    int idx = 0;
    for (auto vec : uf.groups()) {
      // debug(vec);
      for (auto v : vec) {
        mp[A[v]] = idx;
      }
      idx++;
    }
    // debug(mp);
    vl sums(sz);
    rep(i, N) {
      int j = mp[B[i] % M];
      sums[j] += B[i];
    }
    // debug(sums);
    ll ans = 0;
    rep(i, N) ans += B[i];
    ll sum = 0;
    for (auto v : sums) {
      chmax(sum, v);
    }
    ans -= sum;
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