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
  解法
  この問題は、

  N 個のものからいくつか選ぶ 2N 通りの方法を全探索して
  選んだ総和が W に一致するものがあるかどうかを判定する
  という bit
  全探索法のためにあるような問題ですね！まずは、簡潔なコーディングを意識せずに、愚直に「int
  型を vector 型に変換する」という方針で解いてみましょう。

  計算量は、2N 通りそれぞれについて、調べるのに O(N) だけかかるので、O(N2N)
  となります。
*/

vector<int> Int2Vec(int bit, int N) {
  vector<int> S;
  rep(i, N) {
    if (bit & (1 << i)) S.push_back(i);
  }
  return S;
}

int main() {
  /* input */
  int N, W;
  cin >> N >> W;
  vector<int> a(N);
  rep(i, N) cin >> a[i];

  /* solve */
  // bit 全探索
  bool isYes = false;
  rep(bit, 1 << N) {
    // どれを選ぶか
    vector<int> S = Int2Vec(bit, N);
    // その時に対応する総和
    int sum = 0;
    for (auto i : S) sum += a[i];
    // 判定
    if (sum == W) {
      isYes = true;
      break;
    }
  }

  /* output */
  cout << (isYes ? "Yes" : "No") << endl;

  return 0;
}