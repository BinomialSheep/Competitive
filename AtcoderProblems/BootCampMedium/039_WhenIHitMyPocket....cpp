#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

int main() {
  /* input */
  int K, A, B;
  cin >> K >> A >> B;

  /* solve */
  // 円を経由すると損するなら、ずっと叩く
  if (A >= B) {
    cout << K + 1 << endl;
    return 0;
  }
  // A枚あったらBにする
  ll cookie = 1;
  ll yen = 0;
  rep(i, K - 1) {
    if (yen) {
      cookie += B;
      yen--;
    } else if (cookie >= A) {
      yen++;
      cookie -= A;
    } else {
      cookie++;
    }
    // cout << cookie << endl;
  }
  // 最後
  if (yen) {
    cookie += B;
  } else {
    cookie++;
  }

  /* output */
  cout << llMax(cookie, ll(K + 1)) << endl;

  return 0;
}