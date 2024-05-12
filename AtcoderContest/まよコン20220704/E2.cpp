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
  string S;
  int K;

  ll nCk(int n, int k) {
    if (k == 1)
      return n;
    else if (k == 2) {
      return (ll)n * (n - 1) / 2;
    }
    return (ll)n * (n - 1) * (n - 2) / 6;
  }

  ll cntAns(int k, int keta, vvl &cnt, int len) {
    // 残りの0はk箇所
    // 上からk桁目について考える
    if (keta == len - 1) return 1;

    ll ret = 0;

    int top = S[keta] - '0';
    // 0とする分
    if (k != 0 && keta != 0) {
      if (top != 0) {
        ret += cnt[k - 1][len - 1 - keta];
      } else {
        ret += cntAns(k - 1, keta + 1, cnt, len);
      }
    }
    // 1 <= x < s[i]とする分
    if (top >= 2) {
      ret += top * cnt[k][len - 1 - keta - 1];
    }
    // x = s[i]とする分
    if (top >= 1) {
      ret += cntAns(k, keta + 1, cnt, len);
    }
    //   // top - 1以下については自由に選べる
    //   ans += (top - 1) * cnt[len - 1 - i];
    //   // top桁を選んだとすると次の桁も制約がある（次のループで数える）
    return ret;
  }

  void solve() {
    /* input */
    cin >> S;
    cin >> K;

    /* solve */
    int len = (int)S.size();

    vi pow9(4);
    pow9[0] = 1;
    pow9[1] = 9;
    pow9[2] = 9 * 9;
    pow9[3] = 9 * 9 * 9;

    vvl cnt(K, vl(len));
    ll ans = 0;
    // i+1桁の数について考える
    for (int ki = 0; ki < K; ki++) {
      for (int i = 0; i < len - 1; i++) {
        if (i + 1 < ki) continue;
        // どの桁を0以外とするか
        // それを何とするか
        cnt[ki][i] = nCk(i + 1, ki + 1) * pow9[ki + 1];
        if (i != 0) cnt[ki][i] += cnt[ki][i - 1];
      }
    }
    debug(cnt);
    // 上から考える
    // rep(i, len) {
    //   // 上からi桁目
    //   int top = s[i] - '0';
    //   // top - 1以下については自由に選べる
    //   ans += (top - 1) * cnt[len - 1 - i];
    //   // top桁を選んだとすると次の桁も制約がある（次のループで数える）
    // }
    ans = cntAns(K - 1, 0, cnt, len);

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