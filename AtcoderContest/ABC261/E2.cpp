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
    int N, Ca;
    cin >> N >> Ca;
    using bset = bitset<30>;
    bset C = Ca;

    /* solve */
    vi state(30, -1);
    bset xors = 0;
    // 0 0になる
    // 1 1になる

    // 2 XORが偶数
    // 3 XORが奇数

    rep(ti, N) {
      int T, Aa;
      cin >> T >> Aa;
      bset A = Aa;
      // debug(A[0], A[1], A[2]);
      if (T == 1) {
        rep(i, 30) {
          if (A[i] == 0) {
            xors[i] = 0;
            state[i] = 0;
          }
        }
      } else if (T == 2) {
        rep(i, 30) {
          if (A[i] == 1) {
            state[i] = 1;
            xors[i] = 0;
          }
        }
      } else {
        xors ^= A;
      }
      rep(i, 30) {
        if (state[i] == 0) {
          C[i] = 0;
        } else if (state[i] == 1) {
          C[i] = 1;
        }
      }
      C ^= xors;

      ll now = C.to_ullong();
      cout << now << "\n";
    }

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