#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
using vvvi = vector<vector<vector<int>>>;
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

// 左端のindexと右端のindexとその時の最小値のメモ
unordered_map<int, ll> memo;

int getP(int l, int r) { return l * 10000 + r; }

ll rec(int l, int r, vl &A, bool isJoi) {
  // cout << l << " " << r << endl;
  int N = (int)A.size() / 2;
  int p = getP(l, r);

  if (r - l == 0) return 0;
  if (memo[p]) return memo[p];

  if (isJoi) {
    // 兄のターン
    // 両方試す
    ll score1 = rec(l, r - 1, A, !isJoi) + A[r - 1];
    ll score2 = rec(l + 1, r, A, !isJoi) + A[l];
    chmax(memo[p], score1);
    chmax(memo[p], score2);
  } else {
    // 妹のターン
    // 大きい方を取る
    if (A[l] < A[r - 1]) {
      chmax(memo[p], rec(l, r - 1, A, !isJoi));
    } else {
      chmax(memo[p], rec(l + 1, r, A, !isJoi));
    }
  }
  //
  int ql = (l + N) % (2 * N);
  int qr = (r + N) % (2 * N);
  int q = getP(ql, qr);
  memo[q] = memo[p];

  return memo[p];
}

ll solve(int N, vl &A) {
  ll ret = 0;

  // 最初
  rep(i, N) {
    // i個目を最初に選んだ場合
    // 常に[i + 1, i+N)を見ればいい
    int l = i + 1;
    int r = i + N;
    ll score;

    score = rec(l, r, A, false) + A[i];
    chmax(ret, score);
  }
  return ret;
}

int main() {
  /* input */
  int N;
  cin >> N;
  // 簡単のため2倍しておく
  vl A(2 * N);
  rep(i, N) cin >> A[i];
  rep(i, N) A[i + N] = A[i];

  /* solve */
  // 区間dpする
  ll ans = solve(N, A);

  // // debug
  // for (auto p : memo) {
  //   cout << p.first.first << " " << p.first.second << " " << p.second <<
  //   endl;
  // }

  /* output */
  cout << ans << endl;

  return 0;
}