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

int main() {
  /* input */
  int N, M;
  cin >> N >> M;
  vi plush(N);
  rep(i, N) cin >> plush[i];

  /* solve */
  map<int, int> mp;
  rep(i, N) mp[plush[i] - 1]++;

  // ぬいぐるみの累積和を求めておく
  vvi prefixSum(M, vi(N));
  rep(i, N) prefixSum[plush[i] - 1][i] = 1;
  for (int i = 1; i < N; i++) {
    rep(j, M) prefixSum[j][i] += prefixSum[j][i - 1];
  }
  // rep(i, M) {
  //   rep(j, N) { cout << prefixSum[i][j] << " "; }
  //   cout << endl;
  // }

  // dp[bit][Mi] :=
  // bitが1の部分の処理が終わった状態から、Mi種類目を処理した時の最小値
  vl dp((1 << M), INFTY);
  dp[0] = 0;

  rep(bit, (1 << M)) {
    // bitが終わっている
    // 今何個目まで処理できているか
    int start = 0;
    rep(i, M) if (bit & (1 << i)) start += mp[i];
    // あり得ないケース
    rep(j, M) {
      // jに配る
      // もう配ってるなら次
      if (bit & (1 << j)) continue;
      int nexBit = bit | (1 << j);
      // 抜く数
      // startからstart+mp[j]までに含まれるぬいぐるみm以外の数
      int temp = mp[j];
      int cnt = temp;
      // cout << " beforecnt " << cnt << " ";
      // cout << j << " " << start + temp << endl;
      int under = (start == 0 ? 0 : prefixSum[j][start - 1]);
      cnt -= (prefixSum[j][start + temp - 1] - under);

      // cout << " aftercnt " << cnt << " ";
      // cout << bitset<4>(bit) << " " << bitset<4>(nexBit) << " " << endl;
      chmin(dp[nexBit], dp[bit] + cnt);
    }
  }

  /* output */
  // totalling
  int setBit = (1 << M) - 1;
  cout << dp[setBit] << endl;

  return 0;
}