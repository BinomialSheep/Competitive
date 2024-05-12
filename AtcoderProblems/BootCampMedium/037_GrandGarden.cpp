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

vector<int> h;
int ans;

void rec(int l, int r) {
  // 区間l, rに上げる回数を求める
  int num = INFTY;
  int index = -1;
  for (int i = l; i < r; i++) {
    if (num > h[i]) {
      num = h[i];
      index = i;
    }
  }
  // その回数上げる
  for (int i = l; i < r; i++) {
    h[i] -= num;
  }
  ans += num;
  // cout << l << " " << r << " " << index << " " << num << " " << ans << endl;
  // for (int i = l; i < r; i++) {
  //   cout << "h[" << i << "]:" << h[i] << endl;
  // }
  // 左区間と右区間にもう一度上げる
  if (l != index) rec(l, index);
  if (index + 1 != r) rec(index + 1, r);
}

int main() {
  /* input */
  int N;
  cin >> N;
  h.resize(N);
  rep(i, N) cin >> h[i];

  /* solve */
  ans = 0;
  rec(0, N);

  /* output */
  cout << ans << endl;

  return 0;
}