#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

/*
  問題概要
  N 人がいて、それぞれ「正直者」であるか、「不親切な人」であるかのいずれかです。

  「正直者」は、必ず、正しいことを語る
  「不親切な人」は、真偽不明のことを語る (正しいかや誤りかはわからない)
  今、N 人がそれぞれ次のように語りました。

  i 人目は、Ai 個の証言を語った
  i 人目による j 個目の証言は以下のいずれかである
  xi,j さんは「正直者」です (yi,j=1)
  xi,j さんは「不親切な人」です (yi,j=0)
  N
  人それぞれの「正直者」であるか「不親切な人」であるかのパターンのうち、以上の証言に矛盾しないものはいくつか考えられます
  (0
  通りもありえます)。そのうち、正直者が最も多いパターンでは、正直者は何人でしょうか？

  制約
  1≤N≤15
  解法
  この問題は、とにかく方針決めが大切です。以下のような思考に走ってしまうと、迷走します...
  とりあえず、誰かを正直者に決めてみよう...
  人 A を正直者と仮定すると、その人の証言から、B さんと C さんは正直者で、D
  さんは不親切ということになって... そうすると、また B
  さんが正直者ということから、B さんの証言から...
  人間がこの種のパズルを解くとき、こういう風に解くと思いますが、この方針でやると辛いです。
  そこで、次のように考えてみましょう
  誰が正直者で、誰が不親切なのか、完全に決め打ちしてしまう。そのパターンは 2N
  通りある その決め打ちが整合しているのかどうかを check
  する。つまり、証言と矛盾しないかどうかを check する check
  が通ったものについて、正直者の人数を数える。その最大値を出力する。
  ポイントは、「誰が正直者で誰が不親切なのかを完全に決め打ちすると、全員の証言が整合しているかどうかを簡単に確認できる」という点です。実装してみましょう。
*/

// 1つの証言を表す
// firstは人、secondは証言（0 or 1）
using pint = pair<int, int>;

// 入力
int N;
vector<vector<pint>> v;

// 整数 bit に対応する「決め打ち」が整合しているかを判定
bool judge(int bit) {
  // i人目の証言を検証する
  rep(i, N) {
    // i人目が「不親切」だったら無視
    if (!(bit & (1 << i))) continue;
    // i人目が「正直者」なら発言を検証
    for (pint xy : v[i]) {
      int x = xy.first;   // 人 x が
      int y = xy.second;  // y = 1: 正直、y = 0: 不親切

      if (((bit >> x) & 1) ^ y) return false;

      /* 以下のコードをまとめて書いている
      // y = 1なのに「不親切」だったら矛盾
      if (y == 1 && !(bit & (1 << x))) return false;
      // y = 0なのに「正直者」だったら矛盾
      if (y == 0 && (bit & (1 << x))) return false;
      */
    }
  }
  // 矛盾がなければOK
  return true;
}

int main() {
  /* input */
  cin >> N;
  v.resize(N);
  rep(i, N) {
    int A;
    cin >> A;
    v[i].resize(A);
    rep(j, A) {
      cin >> v[i][j].first >> v[i][j].second;
      --v[i][j].first;  // 0-indexedに
    }
  }

  /* solve */
  int res = 0;
  rep(bit, 1 << N) {
    // 矛盾check
    if (judge(bit)) {
      // bitに含まれる人数を数える
      int count = 0;
      rep(i, N) {
        if (bit & (1 << i)) count++;
      }
      res = max(res, count);
    }
  }

  /* output */
  cout << res << endl;

  return 0;
}