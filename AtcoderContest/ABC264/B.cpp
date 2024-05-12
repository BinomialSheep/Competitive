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
    int R, C;
    cin >> R >> C;

    /* solve */
    vs tmp(15);
    tmp[0] = "bbbbbbbbbbbbbbb";
    tmp[1] = "bwwwwwwwwwwwwwb";
    tmp[2] = "bwbbbbbbbbbbbwb";
    tmp[3] = "bwbwwwwwwwwwbwb";
    tmp[4] = "bwbwbbbbbbbwbwb";
    tmp[5] = "bwbwbwwwwwbwbwb";
    tmp[6] = "bwbwbwbbbwbwbwb";
    tmp[7] = "bwbwbwbwbwbwbwb";
    tmp[8] = tmp[6];
    tmp[9] = tmp[5];
    tmp[10] = tmp[4];
    tmp[11] = tmp[3];
    tmp[12] = tmp[2];
    tmp[13] = tmp[1];
    tmp[14] = tmp[0];

    if (tmp[R - 1][C - 1] == 'b') {
      cout << "black" << endl;
    } else {
      cout << "white" << endl;
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