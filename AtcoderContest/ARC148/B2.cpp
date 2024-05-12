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
    string S;
    cin >> N >> S;

    /* solve */
    string ans = S;

    for (int L = 0; L < N; L++) {
      if (S[L] == 'd') continue;
      for (int R = L; R < N; R++) {
        if (S[R] == 'd') continue;
        // debug(L, R);
        for (int i = 0; i <= R; i++) {
          if (L + i > R - i) break;
          if (L + i == R - i) {
            S[L + i] = (S[L + i] == 'd' ? 'p' : 'd');
            break;
          }
          swap(S[L + i], S[R - i]);
          S[L + i] = (S[L + i] == 'd' ? 'p' : 'd');
          S[R - i] = (S[R - i] == 'd' ? 'p' : 'd');
        }
        // debug(S);
        chmin(ans, S);
        for (int i = 0; i <= R; i++) {
          if (L + i > R - i) break;
          if (L + i == R - i) {
            S[L + i] = (S[L + i] == 'd' ? 'p' : 'd');
            break;
          }
          S[L + i] = (S[L + i] == 'd' ? 'p' : 'd');
          S[R - i] = (S[R - i] == 'd' ? 'p' : 'd');
          swap(S[L + i], S[R - i]);
        }
      }
      break;
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