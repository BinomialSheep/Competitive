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
map<pair<int, int>, ll> memo;

ll rec(int l, int r, vl &A) {
  // cout << l << " " << r << endl;
  int N = (int)A.size();
  pair<int, int> p = make_pair(l, r);
  ll al1 = (l != N - 1 ? A[l + 1] : A[0]);
  int l1 = (l != N - 1 ? l + 1 : 0);
  int l2 = (l == N - 2 ? 0 : (l == N - 1 ? 1 : l + 2));
  // int al2 = (l == N - 2 ? A[0] : (l == N - 1 ? A[1] : A[0]));
  ll ar1 = (r == 0 ? A[N - 1] : A[r - 1]);
  ll ar2 = (r == 0 ? A[N - 2] : (r == 1 ? A[N - 1] : A[r - 2]));
  int r1 = (r == 0 ? N - 1 : r - 1);
  int r2 = (r == 0 ? N - 2 : (r == 1 ? N - 1 : r - 2));

  // 取るものが0個
  if (l == r) return 0;
  // 取るものが1個しかない
  if (r - l == 1 || (l == N - 1 && r == 0)) {
    chmax(memo[p], A[l]);
    return A[l];
  }
  // 取るものが2通りだけある(lとr-1)
  if (r - l == 2) {
    chmax(memo[p], llMax(A[l], A[r1]));
    return memo[p];
  }
  if (l == N - 1 && r == 1) {
    chmax(memo[p], llMax(A[l], A[l1]));
    return memo[p];
  }
  if (l == N - 2 && r == 0) {
    chmax(memo[p], llMax(A[l], A[l1]));
    return memo[p];
  }
  // 取るものが3通り以上ある
  // lを取った場合、妹はl+1とr-1から選ぶ

  if (al1 < ar1) {
    // 妹はr-1を選ぶ
    chmax(memo[p], rec(l1, r1, A) + A[l]);
  } else {
    // 妹はl+1を選ぶ
    chmax(memo[p], rec(l2, r, A) + A[l]);
  }
  // rを取った場合、妹はlとr-2から選ぶ
  if (A[l] < ar2) {
    // 妹はr-2を選ぶ
    chmax(memo[p], rec(l, r2, A) + A[r]);
  } else {
    // 妹はlを選ぶ
    chmax(memo[p], rec(l1, r1, A) + A[r]);
  }

  return memo[p];
}

ll solve(int N, vl &A) {
  ll ret = 0;

  // 最初
  rep(i, N) {
    int l = (i == N - 1 ? 0 : i + 1);
    int r = i;
    int l1 = (l != N - 1 ? l + 1 : 0);
    int r1 = (r == 0 ? N - 1 : r - 1);
    ll score;

    if (A[l] < A[r1]) {
      score = rec(l, r1, A) + A[i];
    } else {
      score = rec(l1, r, A) + A[i];
    }
    chmax(ret, score);
  }
  return ret;
}

int main() {
  /* input */
  int N;
  cin >> N;
  vl A(N);
  rep(i, N) cin >> A[i];

  /* solve */
  // 区間dpする
  ll ans = solve(N, A);

  // debug
  for (auto p : memo) {
    cout << p.first.first << " " << p.first.second << " " << p.second << endl;
  }

  /* output */
  cout << ans << endl;

  return 0;
}