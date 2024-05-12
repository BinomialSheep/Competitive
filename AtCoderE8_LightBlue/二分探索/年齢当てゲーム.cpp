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
x = left は「A さんの年齢は x 歳以上である」という条件を満たす
x = right は「A さんの年齢は x 歳以上である」という条件を満たさない
つまり、A さんの年齢の候補が常に left 歳以上 right 歳未満

初期状態は20歳以上36最未満で、狭まってrigh - left = 1となった時にleft歳が答え
*/

int main() {
  /* input */
  int left = 20, right = 36;

  /* solve */
  while (right - left > 1) {
    int mid = left + (right - left) / 2;

    /* mid 歳以上かを聞いて、回答を yes/no で受け取る */
    cout << "Is the age same or more than " << mid << " ? (yes / no)" << endl;
    string ans;
    cin >> ans;

    /* 回答の応じて、年齢を絞る */
    if (ans == "yes")
      left = mid;  // mid 歳以上なら、mid 歳以上 right 歳以下になるように
    else
      right = mid;  // mid 歳未満なら、left 歳以上 mid 歳未満になるように
  }

  /* output */
  /* ズバリ当てる！ */
  cout << "The age is " << left << "!" << endl;

  return 0;
}