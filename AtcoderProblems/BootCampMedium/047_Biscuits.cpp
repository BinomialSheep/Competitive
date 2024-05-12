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

ll comb(int n, int r) {
  vector<vector<ll>> v(n + 1, vector<ll>(n + 1, 0));
  rep(i, v.size()) {
    v[i][0] = 1;
    v[i][i] = 1;
  }
  for (int j = 1; j < v.size(); j++) {
    for (int k = 1; k < j; k++) {
      v[j][k] = (v[j - 1][k - 1] + v[j - 1][k]);
    }
  }
  return v[n][r];
}

int main() {
  /* input */
  int N, P;
  cin >> N >> P;
  vector<int> A(N);
  rep(i, N) cin >> A[i];

  /* solve */
  ll sumA = 0;
  int oddA = 0;
  rep(i, N) {
    sumA += A[i];
    if (A[i] % 2 == 1) {
      oddA++;
    }
  }

  // 奇数個の袋の選び方を求める
  ll oddNum = 0;
  if (sumA % 2 == P) {
    // 奇数個の袋を偶数個選ぶ場合の数
    for (int i = 0; i <= oddA; i += 2) {
      oddNum += comb(oddA, i);
    }
  } else {
    // 奇数個の袋を奇数個選ぶ場合の数
    for (int i = 1; i <= oddA; i += 2) {
      oddNum += comb(oddA, i);
    }
  }

  // 偶数個の袋は何個選んでもいい
  ll evenNum = pow(2LL, N - oddA);

  /* output */
  cout << oddNum * evenNum << endl;

  return 0;
}