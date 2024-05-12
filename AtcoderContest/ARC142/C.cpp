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

    /* solve */

    // 木の直径を求める
    vi dist3(N);
    rep(i, N) {
      int u = 3;
      int v = i + 1;
      if (v == 3) continue;
      cout << "? " << u << " " << v << endl;

      int res;
      cin >> res;
      if (res == -1) return;
      dist3[i] = res;
    }
    int tmp = -1;
    int uIdx = -1;
    rep(i, N) {
      if (chmax(tmp, dist3[i])) {
        uIdx = i + 1;
      }
    }
    vi distU(N);

    rep(i, N) {
      int u = uIdx;
      int v = i + 1;
      if (v + u <= 3) continue;
      if (v == u) continue;
      cout << "? " << u << " " << v << endl;

      int res;
      cin >> res;
      if (res == -1) return;
      distU[i] = res;
    }
    tmp = -1;
    int vIdx = -1;
    rep(i, N) {
      if (chmax(tmp, distU[i])) {
        vIdx = i + 1;
      }
    }
    // 質問は残り2回（もしくは3回）
    debug(uIdx, vIdx);
    if (uIdx >= 3 && vIdx >= 3) {
      int ans = abs(distU[1] - distU[0]);
      cout << "! " << ans << endl;
    } else if (uIdx < 3 && vIdx < 3) {
      // これは直径が答え
      rep(i, N) {
        if (distU[i] == 1) {
          int u = i + 1;
          int v = (uIdx == 1 ? 2 : 1);
          cout << "? " << u << " " << v << endl;
          int res;
          cin >> res;
          //
          cout << "! " << res + 1 << endl;
          return;
        }
      }
    } else {
      // 片方だけ直径の端のパターン
      debug("片方だけ直径の端のパターン");
      if (uIdx == 1 || uIdx == 2) {
        int flag = 0;
        rep(i, N) {
          if (distU[i] == 1) {
            flag = 1;
            int u = i + 1;
            int v = (uIdx == 1 ? 2 : 1);
            debug(u, v);
            cout << "? " << u << " " << v << endl;
            int res;
            cin >> res;
            //
            cout << "! " << res + 1 << endl;
            return;
          }
        }
        if (!flag) {
          // サンプルのパターン
          cout << "! " << 2 << endl;
        }

      } else {
        int k = (vIdx == 1 ? 2 : 1);
        int res1, res2;
        int i1, i2;
        rep(i, N) {
          if (distU[i] == distU[k] - 1) {
            int v = vIdx;
            int u = i + 1;
            i1 = i;
            cout << "? " << u << " " << v << endl;
            cin >> res1;
            break;
          }
        }
        rep(i, N) {
          if (distU[i] == distU[k] + 1) {
            int v = vIdx;
            int u = i + 1;
            i2 = i;
            cout << "? " << u << " " << v << endl;
            cin >> res2;
            break;
          }
        }
        if (distU[i1] + res1 == distU[vIdx] &&
            distU[i2] + res2 == distU[vIdx]) {
          cout << "! " << res1 - 1 << endl;
        } else {
          cout << "! " << res1 - 1 << endl;
        }
        // 嘘
        // if (distU[i] + res == distU[vIdx]) {
        //   cout << "! " << res - 1 << endl;
        // } else {
        //   cout << "! " << res + 1 << endl;
        // }
        return;
      }
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