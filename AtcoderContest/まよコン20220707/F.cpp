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
    vi A(N);
    rep(i, N) cin >> A[i];

    /* solve */

    // dp[i][j] := i桁目を見終えた時の(個数, 合計値）のうち平均値最大
    // jはi桁目を選んだなら1, 選んでないなら0
    using vpil = vector<pair<int, ll>>;
    vector<vpil> dp(N + 1, vpil(2));
    dp[0][1] = make_pair(0, 0);
    rep(i, N) {
      rep(j, 2) {
        if (j == 0) {
          // i+1桁目を選ぶしかない
          int cnt = dp[i][j].first + 1;
          ll sum = dp[i][j].second + A[i];
          double ave0 = (double)sum / cnt;
          double ave1;
          if (dp[i + 1][1].first == 0) {
            ave1 = 0;
          } else {
            ave1 = (double)dp[i + 1][1].second / dp[i + 1][1].first;
          }
          if (ave1 <= ave0) dp[i + 1][1] = make_pair(cnt, sum);
        } else {
          // i+1桁目は選ばなくてもいい
          int cnt = dp[i][j].first + 1;
          ll sum = dp[i][j].second + A[i];
          double ave0 = (double)sum / cnt;
          double ave1;
          if (dp[i + 1][1].first == 0) {
            ave1 = 0;
          } else {
            ave1 = (double)dp[i + 1][1].second / dp[i + 1][1].first;
          }
          double ave2;
          if (dp[i + 1][0].first == 0) {
            ave2 = 0;
          } else {
            ave2 = (double)dp[i + 1][0].second / dp[i + 1][0].first;
          }
          double ave02;
          if (dp[i][1].first == 0) {
            ave02 = 0;
          } else {
            ave02 = (double)dp[i][1].second / dp[i][1].first;
          }

          if (ave1 <= ave0) dp[i + 1][1] = make_pair(cnt, sum);
          if (ave2 <= ave02) dp[i + 1][0] = dp[i][j];
        }
      }
    }
    double ave = 0;
    {
      double ave1 = 0, ave2 = 0;
      if (dp[N][0].first != 0) {
        ave1 = (double)dp[N][0].second / dp[N][0].first;
      }
      if (dp[N][1].first != 0) {
        ave2 = (double)dp[N][1].second / dp[N][1].first;
      }
      ave = max(ave1, ave2);
    }
    debug(ave);
    debug(dp);

    int left = 0;
    int right = 2e9;
    while (right - left > 1) {
      int mid = left + (right - left) / 2;

      vvi dp2(N + 1, vi(2, INFTY));
      dp2[0][1] = 0;

      rep(i, N) {
        if (A[i] >= N) {
          dp2[i + 1][0] = dp2[i + 1][1] = chmin(dp2[i][0], dp2[i][1]);
        } else {
          chmin(dp2[i + 1][1], dp2[i][0] + 1);
          chmin(dp2[i + 1][1], dp2[i][1] + 1);
          chmin(dp2[i + 1][0], dp2[i][1]);
        }
      }

      if (min(dp2[N][0], dp2[N][1]) < (N + 1) / 2 - 1) {
        left = mid;
      } else {
        right = mid;
      }
    }

    int med = left;
    debug(med);
    /* output */
    cout << ave << endl;
    cout << med << endl;
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