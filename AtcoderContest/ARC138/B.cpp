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
  // 逆算する
  int N;
  cin >> N;
  vector<int> A(N);
  rep(i, N) cin >> A[i];
  /* solve */
  int left = 0;
  int right = N - 1;
  int rev = 0;
  while (left != right) {
    if (rev % 2 == 1) {
      A[left];
    }
    // 右端が0なら詰める
    if ((rev % 2 == 0 && A[right] == 0) || (rev % 2 == 1 && A[right] == 1)) {
      right--;
      continue;
    }
    // 左端が1なら終わり
    if ((rev % 2 == 0 && A[left] == 1) || (rev % 2 == 1 && A[left] == 0)) {
      cout << "No" << endl;
      return 0;
    }
    // 左端が0なら反転して詰める
    left++;
    rev++;
  }

  // 1文字になっている
  if (rev % 2 == 0 && A[left] == 0) {
    cout << "Yes" << endl;
  } else if (rev % 2 == 1 && A[left] == 1) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }

  /* output */

  return 0;
}