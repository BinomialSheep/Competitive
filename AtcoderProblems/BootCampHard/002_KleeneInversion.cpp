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
#include <atcoder/all>
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

long long calcInvNum(int maxV, vector<int> &v) {
  ll ret = 0;
  atcoder::fenwick_tree<int> fw(maxV + 2);
  for (int i = 0; i < (int)v.size(); i++) {
    // 自分より大きいのに左側にある数を数える
    // 自分より右側の数 = BITの総和（これまで見た数） - 自分より左側の数
    ret += i - fw.sum(0, v[i] + 1);
    // 自分の位置に1を足す
    fw.add(v[i], 1);
  }
  return ret;
}

struct Solver {
  void solve() {
    /* input */
    int N;
    ll K;
    cin >> N >> K;
    vi A(N);
    rep(i, N) cin >> A[i];

    ll MOD = 1e9 + 7;
    /* solve */
    // Aの中での転倒数
    ll ans = K * (calcInvNum(2000, A) % MOD);
    ans %= MOD;
    // Aと他の間での転倒数を考える
    ll over = 0;
    rep(i, N) {
      rep(j, N) {
        if (A[i] > A[j]) over++;
      }
    }
    over %= MOD;
    ll mul = K * (K - 1) / 2;
    mul %= MOD;
    ans += (over * mul % MOD);
    ans %= MOD;

    /* output */
    // 検証用
    // vi B(N * K);
    // rep(i, K) rep(j, N) B[i * N + j] = A[j];
    // cout << ans << " " << calcInvNum(N * (int)K, B) % MOD << endl;
    // assert(calcInvNum(N * (int)K, B) % MOD == ans);

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