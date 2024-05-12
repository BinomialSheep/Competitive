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
    int H, M;
    cin >> H >> M;

    /* solve */
    for (int i = H; i <= H; i++) {
      for (int j = M; j <= 59; j++) {
        int A = i / 10;
        int B = i % 10;
        int C = j / 10;
        int D = j % 10;
        // string tmp = "";
        // tmp.push_back(char('0' + A));
        // tmp.push_back(char('0' + B));
        // tmp.push_back(':');
        // tmp.push_back(char('0' + C));
        // tmp.push_back(char('0' + D));
        // debug(tmp);
        if (A < 2 || C < 4) {
          if (B <= 5) {
            cout << A << B << " " << C << D << endl;
            return;
          }
        }
      }
    }
    for (int i = H + 1; i <= 23; i++) {
      for (int j = 0; j <= 59; j++) {
        int A = i / 10;
        int B = i % 10;
        int C = j / 10;
        int D = j % 10;
        // string tmp = "";
        // tmp.push_back(char('0' + A));
        // tmp.push_back(char('0' + B));
        // tmp.push_back(':');
        // tmp.push_back(char('0' + C));
        // tmp.push_back(char('0' + D));
        // debug(tmp);
        if (A < 2 || C < 4) {
          if (B <= 5) {
            cout << A << B << " " << C << D << endl;
            return;
          }
        }
      }
    }
    for (int i = 0; i <= 23; i++) {
      for (int j = 0; j <= 59; j++) {
        int A = i / 10;
        int B = i % 10;
        int C = j / 10;
        int D = j % 10;
        if (A < 2 || C < 4) {
          if (B <= 5) {
            cout << A << B << " " << C << D << endl;
            return;
          }
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