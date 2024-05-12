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
    int H, W, K;
    cin >> H >> W >> K;
    vs S(H);
    rep(i, H) cin >> S[i];

    /* solve */
    int ans = INFTY;

    rep(bit, (1 << (H - 1))) {
      bitset<12> bs(bit);
      int cut = bs.count();

      vvl group(cut + 1, vl(W));
      rep(i, W) {
        int idx = 0;
        rep(j, H) {
          if (S[j][i] == '1') group[idx][i]++;
          if (bit & (1 << j)) idx++;
        }
      }
      debug(bs, group);

      // この時点でKを超えていたらどんな切り方でも不可能なので除外
      int skipFlag = 0;
      rep(i, cut + 1) rep(j, W) {
        if (group[i][j] > K) {
          skipFlag = 1;
        }
      }
      if (skipFlag) continue;

      //
      int now = cut;
      vvl prefix(cut + 1, vl(W + 1));
      rep(i, W) {
        int flag = 0;
        rep(j, cut + 1) {
          prefix[j][i + 1] = prefix[j][i] + group[j][i];
          if (prefix[j][i + 1] > K) flag = 1;
        }
        if (flag) {
          // 1個左の行でカットする
          rep(j, cut + 1) prefix[j][i + 1] = group[j][i];
          now++;
        }
      }
      debug(now);
      chmin(ans, now);
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