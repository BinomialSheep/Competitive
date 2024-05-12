#include <bits/stdc++.h>
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
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

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
    vl A(N);
    rep(i, N) cin >> A[i];
    vl X(Q);
    rep(i, Q) cin >> X[i];

    /* solve */
    sort(A.begin(), A.end());
    vl prefixSum(N);
    rep(i, N) {
      if (i == 0)
        prefixSum[i] = A[i];
      else
        prefixSum[i] = prefixSum[i - 1] + A[i];
    }
    // rep(i, N) cout << A[i] << " ";
    // cout << endl;
    // rep(i, N) cout << prefixSum[i] << " ";
    // cout << endl;

    rep(qi, Q) {
      auto it = lower_bound(A.begin(), A.end(), X[qi]);
      // 加算するのはd個
      // 減算し得るのはN - d個
      if (it == A.end()) {
        ll ans = X[qi] * N - prefixSum[N - 1];
        cout << ans << endl;
        continue;
      }
      int d = (int)distance(A.begin(), it);
      // cout << d << " " << prefixSum[d] << endl;
      if (d == 0) {
        ll ans = prefixSum[N - 1] - X[qi] * N;
        cout << ans << endl;
        continue;
      }
      ll ans = 0;
      ll tmp1 = X[qi] * d - prefixSum[d - 1];
      ans += abs(tmp1);
      // cout << ans << " ";
      ll tmp2 = prefixSum[N - 1] - prefixSum[d - 1] - X[qi] * (A.size() - d);
      ans += abs(tmp2);
      // cout << d << " " << tmp1 << " " << tmp2 << " ";
      cout << ans << endl;
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