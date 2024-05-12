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
    vi P(N);
    rep(i, N) cin >> P[i];

    /* solve */
    vector<pair<char, int>> ans;

    // 正しくない側を操作Bで後ろに集める
    rep(j, N) {
      for (int i = 0; i + 2 < N; i += 2) {
        if (P[i] % 2 == 0 && P[i + 2] % 2 != 0) {
          swap(P[i], P[i + 2]);
          ans.emplace_back('B', i + 1);
        }
      }
    }
    rep(j, N) {
      for (int i = 1; i + 2 < N; i += 2) {
        if (P[i] % 2 != 0 && P[i + 2] % 2 == 0) {
          swap(P[i], P[i + 2]);
          ans.emplace_back('B', i + 1);
        }
      }
    }
    // debug(P);
    //  操作Aする
    if (N % 2 == 0) {
      for (int i = 0; i + 1 < N; i += 2) {
        if (P[i] % 2 == 0) {
          swap(P[i], P[i + 1]);
          ans.emplace_back('A', i + 1);
        }
      }
    } else {
      for (int i = 1; i + 1 < N; i += 2) {
        if (P[i] % 2 != 0) {
          swap(P[i], P[i + 1]);
          ans.emplace_back('A', i + 1);
        }
      }
    }
    // debug(P);
    //  操作Bでソート
    rep(j, N) {
      for (int i = 0; i + 2 < N; i += 2) {
        if (P[i] > P[i + 2]) {
          swap(P[i], P[i + 2]);
          ans.emplace_back('B', i + 1);
        }
      }
    }
    rep(j, N) {
      for (int i = 1; i + 2 < N; i += 2) {
        if (P[i] > P[i + 2]) {
          swap(P[i], P[i + 2]);
          ans.emplace_back('B', i + 1);
        }
      }
    }

    // debug(P);

    /* output */
    cout << (int)ans.size() << endl;
    for (auto [b, v] : ans) {
      cout << b << " " << v << "\n";
    }
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