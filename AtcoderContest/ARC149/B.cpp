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
  int lis(vector<int> &A) {
    // L[i]は、長さがi+1であるような増加部分列の最後の要素のうち、最小の値
    // 例えば1, 6, 2, 3ならL[0]=1, L[1]=2, L[2]=3。
    vector<int> L(A.size());
    L[0] = A[0];
    // lenは、i番目の要素までを使った時点の最長増加部分列の長さを表す整数
    int len = 1;

    for (int i = 1; i < A.size(); i++) {
      if (L[len - 1] < A[i]) {
        // 増加部分列の長さを更新できるならする
        L[len++] = A[i];
      } else {
        // よりリーズナブルな増加部分列に置き換えられるならする（二分探索を使ってA[i]以上となる最初の位置を計算）
        *lower_bound(L.begin(), L.begin() + len, A[i]) = A[i];
      }
    }

    return len;
  }

  void solve() {
    /* input */
    int N;
    cin >> N;
    vi A(N);
    rep(i, N) cin >> A[i];
    vi B(N);
    rep(i, N) cin >> B[i];

    /* solve */
    int ans = 0;

    vpii AB;
    rep(i, N) AB.emplace_back(A[i], B[i]);
    vpii BA;
    rep(i, N) BA.emplace_back(B[i], A[i]);
    sort(all(AB));
    rep(i, N) B[i] = AB[i].second;

    chmax(ans, N + lis(B));
    sort(all(BA));
    rep(i, N) A[i] = BA[i].second;
    chmax(ans, N + lis(A));

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