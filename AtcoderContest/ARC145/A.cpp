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
    int len = (int)S.size();

    bool flag = true;
    rep(i, len / 2) {
      char l1 = S[i];
      char l2 = S[i + 1];
      char r1 = S[len - 1 - i];
      char r2 = S[len - 2 - i];
      if (l1 == r1 && l2 == r2) continue;
      if (l1 == 'A' && r1 == 'B') flag = false;
      if (l1 == 'A' && l2 == 'A') {
        if (r2 == 'A' && r1 == 'B') {
          flag = false;
        } else if (r2 == 'B' && r1 == 'A') {
          // change
          S[i + 1] = 'B';
        } else if (r2 == 'B' && r1 == 'B') {
          flag = false;
        }
      } else if (l1 == 'A' && l2 == 'B') {
        if (r2 == 'A' && r1 == 'A') {
          
        } else if (r2 == 'A' && r1 == 'B') {
        } else if (r2 == 'B' && r1 == 'B') {
        }
      } else if (l1 == 'B' && l2 == 'A') {
        if (r2 == 'A' && r1 == 'A') {
        } else if (r2 == 'A' && r1 == 'B') {
        } else if (r2 == 'B' && r1 == 'A') {
        } else if (r2 == 'B' && r1 == 'B') {
        }
      } else if (l1 == 'B' && l2 == 'B') {
        if (r2 == 'A' && r1 == 'A') {
        } else if (r2 == 'A' && r1 == 'B') {
        } else if (r2 == 'B' && r1 == 'A') {
        } else if (r2 == 'B' && r1 == 'B') {
        }
      }
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