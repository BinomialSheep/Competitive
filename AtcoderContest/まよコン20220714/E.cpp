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
    using mint = modint998244353;

    // vector<mint> keta(1e6 + 5);
    // keta[1] = 26;
    // keta[2] = 26;
    // for (int i = 3; i <= 1e6; i += 2) {
    //   keta[i] = keta[i - 2] * 26;
    // }
    // for (int i = 4; i <= 1e6; i += 2) {
    //   keta[i] = keta[i - 2] * 26;
    // }

    // vector<mint> prefix(1e6 + 5);
    // rep(i, 1e6 + 1) prefix[i + 1] = prefix[i] + keta[i + 1];

    vector<mint> pow26(1e6 + 10);
    pow26[0] = 1;
    pow26[1] = 26;
    rep(i, 1e6) { pow26[i + 2] = pow26[i + 1] * 26; }

    int T;
    cin >> T;
    rep(ti, T) {
      /* input */
      int N;
      cin >> N;
      string S;
      cin >> S;
      /* solve */
      mint ans = 0;

      int m = N / 2;
      if (N % 2) {
        rep(i, m) {
          // ギリギリじゃないやつを足していく
          if (S[i] != 'A') {
            ans += (S[i] - 'A') * pow26[m - i - 1] * 26;
          }
        }
        // ギリギリで中央の文字より小さいのは足せる
        ans += S[m] - 'A';
        // ギリギリで中央の文字と同じものを足せるか判定
        int flag = 1;
        rep(i, m) {
          if (S[i + m + 1] > S[m - 1 - i]) break;
          if (S[i + m + 1] < S[m - 1 - i]) flag = 0;
        }
        if (flag) ans++;
      } else {
        // 偶数の場合
        rep(i, m) {
          // ギリギリじゃないやつを足していく
          if (S[i] != 'A') {
            ans += (S[i] - 'A') * pow26[m - i - 1];
          }
          if (ti == 1) debug(i, ans.val());
        }
        // ギリギリを足せるか判定
        int flag = 1;
        rep(i, m) {
          if (S[i + m] > S[m - 1 - i]) break;
          if (S[i + m] < S[m - 1 - i]) flag = 0;
        }
        if (flag) ans++;
      }

      // int m = N / 2;
      // vi keta(m);
      // if (N % 2) {
      //   // 奇数の場合
      //   rep(i, m) { keta[i] = min(S[i], S[i + m + 1]) - 'A' + 1; }
      //   keta.push_back(S[m] - 'A' + 1);
      // } else {
      //   // 偶数の場合
      //   rep(i, m) { keta[i] = min(S[i], S[i + m]) - 'A' + 1; }
      // }
      // rep(i, (int)keta.size()) { ans *= keta[i]; }
      cout << ans.val() << "\n";

      /* output */
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