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
#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

// // 1-indexedなので注意
// struct BIT {
//  private:
//   vector<int> bit;
//   int N;

//  public:
//   BIT(int size) {
//     N = size;
//     bit.resize(N + 1);
//   }

//   // 一点更新（位置aにwを加算）
//   void add(int a, int w) {
//     for (int x = a; x <= N; x += x & -x) bit[x] += w;
//   }

//   // 1～Nの和を求める
//   int sum(int a) {
//     int ret = 0;
//     for (int x = a; x > 0; x -= x & -x) ret += bit[x];
//     return ret;
//   }
// };

// // 第一引数には配列の最大値を入れる
// long long calcInvNum(int n, vector<int> &v) {
//   ll ret = 0;
//   BIT b(n);
//   for (int i = 0; i < n; i++) {
//     // 自分より右側 = BITの総和 - 自分より左側
//     ret += i - b.sum(v[i]);
//     // 自分の位置に1を足す
//     b.add(v[i], 1);
//   }
//   return ret;
// }

long long calcInvNum(int maxV, vector<int> &v) {
  ll ret = 0;
  // 0-indexedなので+1、sumでr+1未満を指定したいので更に+1
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

// 各数における「自分より左にいるのに自分より大きい数」が転倒数
// BITを使ったO(NlogN)の転倒数計算

int main() {
  /* input */
  int n;
  cin >> n;
  vector<int> v(n);
  rep(i, n) cin >> v[i];

  // いいサンプル
  // https://atcoder.jp/contests/chokudai_S001/tasks/chokudai_S001_j

  /* solve */
  ll ans = calcInvNum(n, v);

  // vi v1{3, 1, 5, 4, 2};
  // assert(calcInvNum(5, v1) == 5);
  // cout << "v1 is OK." << endl;
  // vi v2{1, 2, 3, 4, 5, 6};
  // assert(calcInvNum(6, v2) == 0);
  // cout << "v2 is OK." << endl;
  // vi v3{7, 6, 5, 4, 3, 2, 1};
  // assert(calcInvNum(7, v3) == 21);
  // cout << "v3 is OK." << endl;
  // vi v4{19, 11, 10, 7, 8, 9, 17, 18, 20, 4, 3, 15, 16, 1, 5, 15, 6, 2, 13,
  // 12}; assert(calcInvNum(20, v4) == 114); cout << "v4 is OK." << endl; vi
  // v5{5}; assert(calcInvNum(5, v5) == 0); cout << "v5 is OK." << endl;

  /* output */
  cout << ans << endl;

  return 0;
}