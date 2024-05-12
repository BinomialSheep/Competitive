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
    int N, Q;
    cin >> N >> Q;

    dsu uf(1e7);
    int now = N;
    map<int, int> box;
    map<int, int> inv;
    rep(i, N) box[i + 1] = i + 1;
    rep(i, N) inv[i + 1] = i + 1;

    rep(qi, Q) {
      // debug(qi);
      // debug(box);
      // debug(inv);
      // vi temp;
      // rep(i, now) temp.push_back(uf.leader(i + 1));
      // debug(temp);
      int ty;
      cin >> ty;
      if (ty == 1) {
        int X, Y;
        cin >> X >> Y;
        if (inv[Y] == -1) continue;  // 空
        if (inv[X] == -1) {
          box[uf.leader(inv[Y])] = X;
          inv[X] = inv[Y];
          inv[Y] = -1;
        } else {
          uf.merge(inv[X], inv[Y]);
          box[uf.leader(inv[X])] = X;
          inv[X] = uf.leader(inv[X]);
          inv[Y] = -1;
        }
      } else if (ty == 2) {
        int X;
        cin >> X;
        now++;
        if (inv[X] == -1) {
          inv[X] = now;
          box[now] = X;
        } else {
          uf.merge(inv[X], now);
          inv[X] = uf.leader(inv[X]);
        }
      } else {
        int X;
        cin >> X;
        cout << box[uf.leader(X)] << "\n";
      }
    }

    /* solve */

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