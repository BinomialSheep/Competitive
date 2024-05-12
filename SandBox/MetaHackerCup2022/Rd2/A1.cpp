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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    rep(ti, T) {
      /* input */
      string S;
      int Q;
      cin >> S >> Q;

      /* solve */
      vvi prefix((int)S.size(), vi(26));
      rep(i, S.size()) {
        if (i != 0) prefix[i] = prefix[i - 1];
        prefix[i][S[i] - 'a']++;
      }
      // debug(prefix);

      int ans = 0;

      rep(qi, Q) {
        int l, r;
        cin >> l >> r;
        if (r == l) {
          ans++;
          continue;
        }
        if ((r - l) % 2 == 1) continue;
        int idx = ((r + l) / 2) - 1;
        l--;
        r--;
        vi left = prefix[idx - 1];
        vi right = prefix[r];
        if (l != 0) {
          rep(i, 26) left[i] -= prefix[l - 1][i];
        }
        rep(i, 26) right[i] -= prefix[idx][i];

        vi diff;
        int isNG = 0;
        rep(i, 26) {
          if (left[i] == right[i]) continue;
          if (abs(left[i] - right[i]) == 1) {
            diff.push_back(i);
          } else {
            isNG = 1;
            break;
          }
        }
        if (isNG || diff.size() > 2) continue;
        if (diff.size() == 0) {
          ans++;
          // debug("ok", qi);
        } else {
          // assert(diff.size() == 2);
          int tmp = S[idx] - 'a';
          if (tmp == diff[0] || tmp == diff[1]) {
            // debug("ok", qi);
            ans++;
          }
        }
      }

      /* output */
      printf("Case #%d: %d\n", ti + 1, ans);
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