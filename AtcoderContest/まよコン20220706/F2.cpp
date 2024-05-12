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
  double maxSum(vector<double> &a) {
    int n = (int)a.size();
    // dp[N+1][2]と同じだが、pとdpだけ持つことで節約してる
    vector<double> dp(2, -1e18);
    dp[1] = 0;
    rep(i, n) {
      vector<double> p(2, -1e18);
      swap(dp, p);
      rep(j, 2) {
        // 直前を選んでいてもいなくても今回選べる
        chmax(dp[1], p[j] + a[i]);
        // 直前を選んでいるなら今回は選ばないこともできる
        if (j) chmax(dp[0], p[j]);
      }
    }
    return max(dp[0], dp[1]);
  }

  double solveAve(vi &A) {
    int N = (int)A.size();
    double ac = 0, wa = 1e9;
    rep(ti, 50) {
      double wj = (ac + wa) / 2;
      // 平均をwj以上にできるならOK
      vector<double> na(N);
      rep(i, N) na[i] = A[i] - wj;
      if (maxSum(na) >= 0) {
        ac = wj;
      } else {
        wa = wj;
      }
    }
    return ac;
  }

  bool canMedOne(vi &a) {
    int n = (int)a.size();
    int one = 0;
    rep(i, n) if (a[i] == 1) one++;
    // nowは今の連続する0の個数
    int zero = 0, now = 0;
    rep(i, n) {
      if (a[i] == 1) {
        zero += now / 2;
        now = 0;
      } else {
        now++;
      }
      zero += now / 2;
    }
    return zero <= one - 1;
  }

  int solveMed(vi &a) {
    int n = (int)a.size();
    int ac = 1, wa = 1e9 + 9;
    while (wa - ac > 1) {
      int wj = (ac + wa) / 2;
      vi na(n);
      rep(i, n) na[i] = a[i] >= wj;
      if (canMedOne(na)) {
        ac = wj;
      } else {
        wa = wj;
      }
    }

    return ac;
  }

  void solve() {
    /* input */
    int N;
    cin >> N;
    vi A(N);
    rep(i, N) cin >> A[i];

    /* solve */

    /* output */
    printf("%.4f\n", solveAve(A));
    cout << solveMed(A) << endl;
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