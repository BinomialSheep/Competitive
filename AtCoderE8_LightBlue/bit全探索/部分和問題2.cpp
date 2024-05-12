#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

/*
  けんちょんさんの記事からbit全探索の勉強として写経
  https://drken1215.hatenablog.com/entry/2019/12/14/171657
  問題概要
  N 個の正の整数 a0,a1,…,aN−1 と、正の整数 W とが与えられます。

  a0,a1,…,aN−1 の中から何個か選んで総和を W
  とすることができるかどうかを判定してください。

  制約
  1≤N≤20

  1と同じ問題だが、こちらの方が簡略
*/
int main() {
  /* input */
  int N, W;
  cin >> N >> W;
  vector<int> a(N);
  rep(i, N) cin >> a[i];

  /* solve */
  // bit 全探索
  rep(bit, 1 << N) {
    int sum = 0;
    rep(i, N) {
      if (bit & (1 << i)) sum += a[i];
    }
    if (sum == W) {
      cout << "Yes" << endl;
      return 0;
    }
  }

  /* output */
  cout << "No" << endl;

  return 0;
}