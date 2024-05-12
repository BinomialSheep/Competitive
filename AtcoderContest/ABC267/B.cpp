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
    string S;
    cin >> S;

    /* solve */
    bool isYes = false;

    vb B(7, false);
    if (S[6] == '0') B[0] = true;
    if (S[3] == '0') B[1] = true;
    if (S[1] == '0' && S[7] == '0') B[2] = true;
    if (S[0] == '0' && S[4] == '0') B[3] = true;
    if (S[2] == '0' && S[8] == '0') B[4] = true;
    if (S[5] == '0') B[5] = true;
    if (S[9] == '0') B[6] = true;

    if (S[0] == '0') {
      for (int i = 0; i < 5; i++) {
        for (int j = i + 2; j < 7; j++) {
          if (!B[i] && !B[j]) {
            for (int k = i + 1; k < j; k++) {
              if (B[k]) isYes = true;
            }
          }
        }
      }
    }

    /* output */
    cout << (isYes ? "Yes" : "No") << endl;
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