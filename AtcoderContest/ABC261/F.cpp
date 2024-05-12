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
    vi C(N);
    rep(i, N) cin >> C[i];
    vi X(N);
    rep(i, N) cin >> X[i];

    /* solve */
    ll ans = 0;
    {
      fenwick_tree<int> fw(N + 2);
      rep(i, N) {
        ans += i - fw.sum(0, X[i] + 1);
        fw.add(X[i], 1);
      }
    }

    map<int, vector<int>> mp;
    // map<int, vector<int>> idxs;
    rep(i, N) {
      mp[C[i]].push_back(X[i]);
      // idxs[C[i]].push_back(i);
    }
    for (auto [c, st] : mp) {
      // vi idx = idxs[c];
      // int i = 0;
      // for (auto num : st) {
      //   X[idx[i]] = num;
      //   i++;
      // }
      fenwick_tree<int> fw(N + 2);
      rep(i, (int)st.size()) {
        ans -= i - fw.sum(0, st[i] + 1);
        fw.add(st[i], 1);
      }
    }
    // debug(X);

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